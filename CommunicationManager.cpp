/*
 * CommunicationManager.cpp
 *
 *  Created on: 13 черв. 2014
 *      Author: maximm
 */

#include "CommunicationManager.h"
#include "Log.h"
#include <boost/lexical_cast.hpp>
#include <stdio.h>
#include <sys/types.h>

CommunicationManager::CommunicationManager() : m_run(true), m_listenSocket(0)
{
}

CommunicationManager::~CommunicationManager()
{
}

void CommunicationManager::Connect( const std::string &addr, const unsigned port )
{

}

void CommunicationManager::Listen( const std::string &addr, const unsigned port )
{
	Log::Add( "Start listen on " + addr + ":" + boost::lexical_cast<std::string>(port) );

	if ( WSAStartup(0x202, &m_wsaData) != 0 )
	{
		Log::Add( "Failed to init data" );
		return;
	}

	sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons( port );
	local.sin_addr.s_addr = ( addr == "*" ) ? INADDR_ANY : inet_addr( addr.c_str() );

	m_listenSocket = socket( AF_INET, SOCK_STREAM, 0 );

	if ( m_listenSocket == INVALID_SOCKET)
	{
		Log::Add( "Failed to listen socket" );
		return;
	}

	if ( bind( m_listenSocket, (struct sockaddr*)&local, sizeof(local) ) == SOCKET_ERROR)
	{
		Log::Add( "Failed to bind socket" );
		return;
	}

	if ( listen( m_listenSocket, 1024 ) == SOCKET_ERROR)
	{
		Log::Add( "Failed to listen socket" );
		return;
	}

	u_long NonBlock = 1;
	if ( ioctlsocket( m_listenSocket, FIONBIO, &NonBlock ) == SOCKET_ERROR )
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
	WSACleanup();
	Log::Add( "All connections closed" );
}

void CommunicationManager::Update()
{
	sockaddr_in fromAddr;
	int fromLen = sizeof(fromAddr);
	SOCKET msgsock(0);
	fd_set readSet;
	FD_ZERO(&readSet);
	FD_SET(m_listenSocket, &readSet);
	timeval timeout;
	timeout.tv_sec = 1;  // Zero timeout (poll)
	timeout.tv_usec = 0;
	Log::Add( "Select" );
	if( select(m_listenSocket, &readSet, NULL, NULL, &timeout) == 1)
	{
		msgsock = accept( m_listenSocket, (sockaddr *)&fromAddr, &fromLen );
		Log::Add( boost::lexical_cast<std::string>(m_listenSocket) );

		if ( msgsock == INVALID_SOCKET )
		{
			Log::Add(  boost::lexical_cast<std::string>( WSAGetLastError() ) );
			return;
		}
		Log::Add( "Server: accepted connection from " + std::string( inet_ntoa(fromAddr.sin_addr) ) + ", port " + boost::lexical_cast<std::string>(htons(fromAddr.sin_port) ) );
	}
}

void *CommunicationManager::Run( void *arg )
{
	 Log::Add( "Create thread" );
	 CommunicationManager *comm = (CommunicationManager*) arg;
	 while ( comm->m_run )
	 {
		 comm->Update();
	 }
	 Log::Add( "End thread" );
	 pthread_exit(NULL);
	 return NULL;
}
