/*
 * CommunicationServer.cpp
 *
 *  Created on: 23 лип. 2014
 *      Author: maximm
 */

#include "CommunicationServer.h"
#include "Log.h"
#include <algorithm>

CommunicationServer::CommunicationServer() : m_clientsM(0)
{
}

CommunicationServer::~CommunicationServer()
{
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

Client* CommunicationServer::CreateInputConn()
{
	fd_set readSet;
	FD_ZERO(&readSet);
	FD_SET(m_socket, &readSet);
	Client *client = NULL;

	if( select(m_socket, &readSet, NULL, NULL, &m_timeout) == 1)
	{
		client = new Client( this );
		int fromLen = sizeof(client->addr);
		client->socket = accept( m_socket, (sockaddr *)&client->addr, &fromLen );

		if ( client->socket == INVALID_SOCKET )
		{
			Log::Add( "Failed init socket for connection: " + Log::IntToStr( WSAGetLastError() ) );
			delete client;
			return NULL;
		}
	}

	return client;
}

Client& CommunicationServer::StoreClient( Client &client  )
{
	pthread_mutex_lock( &m_clientsM );
	Log::Add( "Add client: " + Log::AddrToStr( client.addr ) );
	m_clients.push_back( client );
	Client& sclient = m_clients.back();
	pthread_mutex_unlock( &m_clientsM );
	return sclient;
}

void CommunicationServer::RemoveClient( const Client& data )
{
	pthread_mutex_lock( &m_clientsM );
	Clients::iterator it = std::find( m_clients.begin(), m_clients.end(), data );
	if( it !=  m_clients.end() )
	{
		Log::Add( "Remove client: " + Log::AddrToStr( data.addr ) );
		m_clients.erase( it );
	}
	pthread_mutex_unlock( &m_clientsM );
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
		Client *data = comm->CreateInputConn();
		comm->CreateHandlerThread( data );
		delete data;
	}
	Log::Add( "End listen thread" );
	pthread_exit(NULL);
	return NULL;
}

void CommunicationServer::CreateHandlerThread( Client *data )
{
	if ( data == NULL )
	{
		return;
	}

	Client &client = StoreClient( *data );
	pthread_create( &data->thread, NULL, &DataHandlerThr, (void*)&client);
}

void *CommunicationServer::DataHandlerThr( void *arg )
{
	if ( !arg )
	{
		Log::Add( "Null pointer in connection thread" );
		return NULL;
	}
	Log::Add( "Start handler thread" );
	Client *data = (Client*) arg;
	Log::Add( "Server: accepted connection from " + Log::AddrToStr( data->addr ) );
	ReadSocket( data->socket, data->manager->m_run );
	Log::Add( "Server: disconnected from " + Log::AddrToStr( data->addr ) );
	data->manager->RemoveClient( *data );
	delete data;
	Log::Add( "End handler thread" );
	pthread_exit(NULL);
	return NULL;
}

void CommunicationServer::CloseAdditionalThreads()
{
	for ( Clients::iterator iter = m_clients.begin(); iter != m_clients.end(); iter++ )
	{
		pthread_join( iter->thread, NULL );
	}
}
