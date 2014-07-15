/*
 * CommunicationManager.cpp
 *
 *  Created on: 13 черв. 2014
 *      Author: maximm
 */

#include "CommunicationManager.h"
#include "Log.h"
#include <stdio.h>
#include <sys/types.h>
#include <algorithm>

CommunicationManager::CommunicationManager() : m_run(true), m_socket(0)
{
}

CommunicationManager::~CommunicationManager()
{
}

void CommunicationManager::Init()
{
	m_timeout.tv_sec = 1;  // Zero timeout (poll)
	m_timeout.tv_usec = 0;
}

void CommunicationManager::Connect( const std::string &addr, const unsigned port )
{
	Log::Add( "Try connect to " + addr + ":" + Log::IntToStr( port ) );
	if ( WSAStartup(0x202, &m_wsaData) != 0 )
	{
		Log::Add( "Failed to init data" );
		return;
	}

	unsigned long remote = inet_addr( addr.c_str() );
	hostent* host = gethostbyaddr((char *)&remote, 4, AF_INET);

	if ( !host )
	{
		Log::Add( "Failed get host by address" );
	}

	sockaddr_in address;
	memset(&address, 0, sizeof(address));
	memcpy(&(address.sin_addr), host->h_addr, host->h_length);
	address.sin_family = host->h_addrtype;
	address.sin_port = htons(port);

	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if ( m_socket == INVALID_SOCKET)
	{
		Log::Add( "Failed to open socket" );
		return;
	}

	if ( connect(m_socket, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR )
	{
		Log::Add( "Failed to connect" );
		return;
	}

	Log::Add( "Connected to " + addr + ":" + Log::IntToStr( port ) );
}

void CommunicationManager::Listen( const std::string &addr, const unsigned port )
{
	Log::Add( "Socket listen on " + addr + ":" + Log::IntToStr( port ) );

	if ( WSAStartup(0x202, &m_wsaData) != 0 )
	{
		Log::Add( "Failed to init data" );
		return;
	}

	sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons( port );
	local.sin_addr.s_addr = ( addr == "*" ) ? INADDR_ANY : inet_addr( addr.c_str() );

	m_socket = socket( AF_INET, SOCK_STREAM, 0 );

	if ( m_socket == INVALID_SOCKET)
	{
		Log::Add( "Failed to open socket" );
		return;
	}

	if ( bind( m_socket, (struct sockaddr*)&local, sizeof(local) ) == SOCKET_ERROR)
	{
		Log::Add( "Failed to bind socket" );
		return;
	}

	if ( listen( m_socket, 1024 ) == SOCKET_ERROR)
	{
		Log::Add( "Failed to listen socket" );
		return;
	}

	u_long NonBlock = 1;
	if ( ioctlsocket( m_socket, FIONBIO, &NonBlock ) == SOCKET_ERROR )
	{
		Log::Add( "Setting non blocking failed" );
	}

	pthread_create( &m_mainThread, NULL, &Run, (void*)this);
}

void CommunicationManager::Close()
{
	Log::Add( "Close all connections" );
	m_run = false;
	pthread_join( m_mainThread, NULL );
	closesocket( m_socket );
	WSACleanup();
	Log::Add( "All connections closed" );
}

void CommunicationManager::Update()
{

	fd_set readSet;
	FD_ZERO(&readSet);
	FD_SET(m_socket, &readSet);

	if( select(m_socket, &readSet, NULL, NULL, &m_timeout) == 1)
	{
		sockaddr_in fromAddr;
		int fromLen = sizeof(fromAddr);

		SOCKET& msgsock = CreateConnectedSocket( accept( m_socket, (sockaddr *)&fromAddr, &fromLen ) );
		if ( msgsock == INVALID_SOCKET )
		{
			Log::Add(  Log::IntToStr( WSAGetLastError() ) );
			return;
		}
		Log::Add( "Server: accepted connection from " + std::string( inet_ntoa(fromAddr.sin_addr) ) + ", port " + Log::IntToStr( htons(fromAddr.sin_port) ) );

		CloseConnectedSocket(msgsock);
	}
}

SOCKET& CommunicationManager::CreateConnectedSocket( const SOCKET &socket )
{
	m_connected.push_back(socket);
	return m_connected.back();
}

void CommunicationManager::CloseConnectedSocket( const SOCKET &socket )
{
	Sockets::iterator sock = std::find( m_connected.begin(), m_connected.end(), socket );
	if ( sock == m_connected.end() )
	{
		closesocket(socket);
	}
	else
	{
		closesocket( *sock );
		m_connected.erase( sock );
	}
}


void *CommunicationManager::Run( void *arg )
{
	if ( !arg )
	{
		Log::Add( "Null pointer in listen thread" );
		return NULL;
	}

	Log::Add( "Start listen thread" );
	CommunicationManager *comm = (CommunicationManager*) arg;
	while ( comm->m_run )
	{
		comm->Update();
	}
	Log::Add( "End listen thread" );
	pthread_exit(NULL);
	return NULL;
}
