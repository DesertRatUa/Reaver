/*
 * CommunicationServer.cpp
 *
 *  Created on: 23 лип. 2014
 *      Author: maximm
 */

#include "ServerCommunicationManager.h"
#include "Log.h"
#include <algorithm>
#include "MessageProcessor.h"
#include "ServerModule.h"

ServerCommunicationManager::ServerCommunicationManager( ServerModule &server, MessageProcessor &processor, bool &isRun  ) : m_clientsM(0), CommunicationManager( processor, isRun ), m_server( server )
{
}

ServerCommunicationManager::~ServerCommunicationManager()
{
}

void ServerCommunicationManager::Init()
{
	CommunicationManager::Init();
	pthread_mutex_init( &m_clientsM, NULL );
}

void ServerCommunicationManager::Listen( const std::string &addr, const unsigned port ) throw( std::runtime_error )
{
	Log::Add( "Try listen on " + addr + ":" + Log::IntToStr( port ) );
	m_run = true;
	m_address.sin_family = AF_INET;
	m_address.sin_port = htons( port );
	m_address.sin_addr.s_addr = ( addr == "*" ) ? INADDR_ANY : inet_addr( addr.c_str() );

	if ( bind( m_socket, (sockaddr*) &m_address, sizeof(m_address) ) == SOCKET_ERROR)
	{
		throw( std::runtime_error( "Failed to bind socket" ));
	}

	if ( listen( m_socket, 1024 ) == SOCKET_ERROR)
	{
		throw( std::runtime_error( "Failed to listen socket" ));
	}

	u_long NonBlock = 1;
	if ( ioctlsocket( m_socket, FIONBIO, &NonBlock ) == SOCKET_ERROR )
	{
		throw( std::runtime_error( "Setting non blocking failed" ));
	}

	Log::Add( "Listen on " + addr + ":" + Log::IntToStr( port ) );

	pthread_create( &m_mainThread, NULL, &ListenSocketThr, (void*)this);
}

ClientPtr ServerCommunicationManager::CreateInputConn()
{
	fd_set readSet;
	FD_ZERO(&readSet);
	FD_SET(m_socket, &readSet);
	ClientPtr client;

	if( select(m_socket, &readSet, NULL, NULL, &m_timeout) == 1)
	{
		client.reset( new Client( this ) );
		int fromLen = sizeof(client->addr);
		client->socket = accept( m_socket, (sockaddr *)&client->addr, &fromLen );
		if ( client->socket == INVALID_SOCKET )
		{
			Log::Add( "Failed init socket for connection: " + Log::IntToStr( WSAGetLastError() ) );
			client.reset();
		}
	}
	return client;
}

ClientPtr* ServerCommunicationManager::StoreClient( ClientPtr& client  )
{
	pthread_mutex_lock( &m_clientsM );
	Log::Add( "Store client: " + Log::AddrToStr( client->addr ) );
	m_clients.push_back( client );
	ClientPtr *cl = &m_clients.back();
	pthread_mutex_unlock( &m_clientsM );
	return cl;
}

void ServerCommunicationManager::RemoveClient( const ClientPtr& client)
{
	pthread_mutex_lock( &m_clientsM );
	Clients::iterator it = std::find( m_clients.begin(), m_clients.end(), client );
	if( it !=  m_clients.end() )
	{
		std::string addr =  Log::AddrToStr( (*it)->addr );
		Log::Add( "Remove client: " + addr );
		m_server.UnregisterNode( addr );
		m_clients.erase( it );
	}
	else
	{
		Log::Add( "Client: " + Log::AddrToStr( client->addr ) +" not found" );
	}
	pthread_mutex_unlock( &m_clientsM );
}

Client& ServerCommunicationManager::GetClient( const std::string &addr )
{
	Client* client = NULL;
	pthread_mutex_lock( &m_clientsM );
	for( Clients::iterator it = m_clients.begin(); it != m_clients.end(); ++it )
	{
		if ( Log::AddrToStr( (*it)->addr ) == addr )
		{
			client = it->get();
			break;
		}
	}
	pthread_mutex_unlock( &m_clientsM );
	if ( !client )
	{
		throw( std::runtime_error( "Client: " + addr + "  not found!" ) );
	}
	return *client;
}

void *ServerCommunicationManager::ListenSocketThr( void *arg )
{
	if ( !arg )
	{
		Log::Add( "Null pointer in listen thread" );
		return NULL;
	}

	Log::Add( "Start listen thread" );
	ServerCommunicationManager *comm = (ServerCommunicationManager*) arg;
	while ( comm->m_run )
	{
		ClientPtr client = comm->CreateInputConn();
		if ( client.get() )
		{
			comm->CreateHandlerThread( client );
		}
	}
	Log::Add( "End listen thread" );
	//pthread_exit(NULL);
	return NULL;
}

void ServerCommunicationManager::CreateHandlerThread( ClientPtr &client )
{
	Log::Add( "Start handler thread" );
	pthread_create( &client->thread, NULL, &DataHandlerThr, (void*)StoreClient( client ) );
}

void *ServerCommunicationManager::DataHandlerThr( void *arg )
{
	if ( !arg )
	{
		Log::Add( "Null pointer in connection thread" );
		return NULL;
	}

	ClientPtr client( *(ClientPtr*)arg );
	std::string addr = Log::AddrToStr( client->addr );
	Log::Add( "Connected from " + addr );
	ReadSocket( client->socket, client->manager, addr );
	Log::Add( "Disconnected from " + addr );
	client->manager->RemoveClient( client );
	Log::Add( "End handler thread" );
	//pthread_exit(NULL);
	return NULL;
}

void ServerCommunicationManager::CloseAdditionalThreads()
{
	for ( Clients::iterator iter = m_clients.begin(); iter != m_clients.end(); iter++ )
	{
		pthread_join( (*iter)->thread, NULL );
	}
}
