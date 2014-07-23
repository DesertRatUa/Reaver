/*
 * CommunicationServer.cpp
 *
 *  Created on: 23 лип. 2014
 *      Author: maximm
 */

#include "CommunicationServer.h"
#include "Log.h"

CommunicationServer::CommunicationServer() : m_clientsM(0)
{
}

CommunicationServer::~CommunicationServer()
{
}

CommunicationServer::SocketData::SocketData( CommunicationServer *Manager ) : manager(Manager), socket(0)
{
	memset( &addr, 0, sizeof(addr) );
}

void CommunicationServer::Init()
{
	CommunicationManager::Init();
	pthread_mutex_init( &m_clientsM, NULL );
}

void CommunicationServer::Listen( const std::string &addr, const unsigned port )
{
	Log::Add( "Try listen on " + addr + ":" + Log::IntToStr( port ) );

	m_address.sin_family = AF_INET;
	m_address.sin_port = htons( port );
	m_address.sin_addr.s_addr = ( addr == "*" ) ? INADDR_ANY : inet_addr( addr.c_str() );

	if ( bind( m_socket, (sockaddr*) &m_address, sizeof(m_address) ) == SOCKET_ERROR)
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

	pthread_create( &m_mainThread, NULL, &ListenSocketThr, (void*)this);
}

CommunicationServer::SocketData* CommunicationServer::CreateInputConn()
{
	fd_set readSet;
	FD_ZERO(&readSet);
	FD_SET(m_socket, &readSet);
	SocketData *data = NULL;

	if( select(m_socket, &readSet, NULL, NULL, &m_timeout) == 1)
	{
		data = &AddClient();
		int fromLen = sizeof(data->addr);
		data->socket = accept( m_socket, (sockaddr *)&data->addr, &fromLen );

		if ( data->socket == INVALID_SOCKET )
		{
			Log::Add( "Failed init socket for connection: " + Log::IntToStr( WSAGetLastError() ) );
			RemoveClient( *data );
			return NULL;
		}
	}

	return data;
}

CommunicationServer::SocketData& CommunicationServer::AddClient()
{
	pthread_mutex_lock( &m_clientsM );
	m_clients.push_back( SocketData( this ) );
	SocketData& client = m_clients.back();
	pthread_mutex_unlock( &m_clientsM );
	return client;
}

void CommunicationServer::RemoveThread( const pthread_t *thread )
{
	if ( !thread )
	{
		return;
	}
	pthread_mutex_lock( &m_threadList );
	/*
	for ( ThreadsList::iterator iter = m_listenThreads.begin(); iter != m_listenThreads.end(); iter++ )
	{
		if ( thread->p == iter->p )
		{
			m_listenThreads.erase( iter );
			break;
		}
	}
	 */
	pthread_mutex_unlock( &m_threadList );
}


void *CommunicationServer::ListenSocketThr( void *arg )
{
	if ( !arg )
	{
		Log::Add( "Null pointer in listen thread" );
		return NULL;
	}

	Log::Add( "Start listen thread" );
	CommunicationServer *comm = (CommunicationServer*) arg;
	while ( comm->m_run )
	{
		SocketData *data = comm->CreateInputConn();
		comm->CreateHandlerThread( data );
	}
	Log::Add( "End listen thread" );
	pthread_exit(NULL);
	return NULL;
}

void CommunicationServer::CreateHandlerThread( SocketData *data )
{
	if ( data == NULL )
	{
		return;
	}

	data->thread = &AddThread();
	pthread_create( data->thread, NULL, &DataHandlerThr, (void*)data );
}

void *CommunicationServer::DataHandlerThr( void *arg )
{
	if ( !arg )
	{
		Log::Add( "Null pointer in connection thread" );
		return NULL;
	}
	Log::Add( "Start handler thread" );
	SocketData *data = (SocketData*) arg;
	Log::Add( "Server: accepted connection from " + std::string( inet_ntoa( data->addr.sin_addr ) ) + ":" + Log::IntToStr( htons( data->addr.sin_port ) ) );
	ReadSocket( data->socket, data->manager->m_run );
	Log::Add( "Server: disconnected from " + std::string( inet_ntoa( data->addr.sin_addr ) ) + ":" + Log::IntToStr( htons( data->addr.sin_port ) ) );
	data->manager->RemoveThread( data->thread );
	delete data;
	Log::Add( "End handler thread" );
	pthread_exit(NULL);
	return NULL;
}

void CommunicationServer::CloseAdditionalThreads()
{
	/*
	for ( ThreadsList::iterator iter = m_listenThreads.begin(); iter != m_listenThreads.end(); iter++ )
	{
		pthread_exit( &(*iter) );
	}
	*/
}
