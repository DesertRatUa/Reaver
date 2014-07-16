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

CommunicationManager::CommunicationManager() : m_run(true), m_socket(0), m_threadList(NULL)
{
}

CommunicationManager::~CommunicationManager()
{
}

CommunicationManager::SocketData::SocketData( CommunicationManager *Manager, pthread_t &Thread ) : manager(Manager), socket(0), thread(&Thread)
{
	memset( &addr, sizeof(addr), 0 );
}

void CommunicationManager::Init()
{
	m_timeout.tv_sec = 1;  // Zero timeout (poll)
	m_timeout.tv_usec = 0;
	pthread_mutex_init( &m_threadList, NULL );
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

	std::string message( "Test message 1 2 3" );
	Sleep(1000);

	for ( unsigned i = 0; i < 5; ++i )
	{
		send( m_socket, message.c_str(), message.length(), 0);
		Sleep(1000);
	}

}

void CommunicationManager::Listen( const std::string &addr, const unsigned port )
{
	Log::Add( "Try listen on " + addr + ":" + Log::IntToStr( port ) );

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

	Log::Add( "Listen on " + addr + ":" + Log::IntToStr( port ) );

	pthread_create( &m_mainThread, NULL, &Run, (void*)this);
}

void CommunicationManager::Close()
{
	Log::Add( "Close all connections" );
	m_run = false;
	pthread_join( m_mainThread, NULL );
	closesocket( m_socket );
	for ( ThreadsList::iterator iter = m_listenThreads.begin(); iter != m_listenThreads.end(); iter++ )
	{
		pthread_exit( &(*iter) );
	}
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
		SocketData *data = new SocketData( this, AddThread() );
		int fromLen = sizeof(data->addr);
		data->socket = accept( m_socket, (sockaddr *)&data->addr, &fromLen );

		if ( data->socket == INVALID_SOCKET )
		{
			Log::Add( "Failed init socket for connection: " + Log::IntToStr( WSAGetLastError() ) );
			RemoveThread( data->thread );
			delete data;
			return;
		}
		Log::Add( "Server: accepted connection from " + std::string( inet_ntoa( data->addr.sin_addr ) ) + ", port " + Log::IntToStr( htons( data->addr.sin_port ) ) );
		pthread_create( data->thread, NULL, &ConnectionThread, (void*)data );
	}
}

pthread_t& CommunicationManager::AddThread()
{
	pthread_mutex_lock( &m_threadList );
	m_listenThreads.push_back( pthread_t() );
	pthread_t& thread = m_listenThreads.back();
	pthread_mutex_unlock( &m_threadList );
	return thread;
}

void CommunicationManager::RemoveThread( const pthread_t *thread )
{
	if ( !thread ) return;
	pthread_mutex_lock( &m_threadList );
	for ( ThreadsList::iterator iter = m_listenThreads.begin(); iter != m_listenThreads.end(); iter++ )
	{
		if ( thread->p == iter->p )
		{
			m_listenThreads.erase( iter );
			break;
		}
	}
	pthread_mutex_unlock( &m_threadList );
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

void *CommunicationManager::ConnectionThread( void *arg )
{
	if ( !arg )
	{
		Log::Add( "Null pointer in connection thread" );
		return NULL;
	}
	Log::Add( "Start connection thread" );
	SocketData *data = (SocketData*) arg;

	char Buffer[256];
	memset( Buffer, sizeof(Buffer), 0 );

	/*
	u_long NonBlock = 0;
	if ( ioctlsocket( data->socket, FIONBIO, &NonBlock ) == SOCKET_ERROR )
	{
		Log::Add( "Setting blocking failed" );
	}
	*/

	fd_set readSet;
	FD_ZERO(&readSet);
	FD_SET( data->socket , &readSet);

	int status = select( data->socket, &readSet, NULL, NULL, &data->manager->m_timeout);
	while ( status != SOCKET_ERROR )
	{
		if( status == 0 )
		{

			continue;
		}

		if( status == SOCKET_ERROR )
		{
			Log::Add( "Failed get connection from client: " + Log::IntToStr( WSAGetLastError() ) );
			continue;
		}

		status = recv( data->socket, Buffer, sizeof(Buffer), 0 );

		if ( status == 0 )
		{
			Log::Add( "Client disconnected" );
			break;
		}

		if( status == SOCKET_ERROR )
		{
			Log::Add( "Failed get data from client: " + Log::IntToStr( WSAGetLastError() ) );
		}
		Log::Add( "Recived: " + std::string(Buffer) );
		memset( Buffer, sizeof(Buffer), 0 );

		status = select( data->socket, &readSet, NULL, NULL, &data->manager->m_timeout);
	}


	if ( status == 0 )
	{

	}

	closesocket( data->socket );
	Log::Add( "End connection thread" );
	data->manager->RemoveThread( data->thread );
	delete data;
	pthread_exit(NULL);
	return NULL;
}
