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
#include <thread>

ServerCommunicationManager::ServerCommunicationManager( ServerModule &server, MessageProcessor &processor, bool &isRun  ) :
	CommunicationManager( processor, isRun ), m_server( server )
{
}

ServerCommunicationManager::~ServerCommunicationManager()
{
}

void ServerCommunicationManager::Init()
{
	CommunicationManager::Init();
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

	m_mainThread.reset( new std::thread( ServerCommunicationManager::ListenSocketThread, std::ref ( *this ) ) );
}

ClientPtr ServerCommunicationManager::CreateInputConn()
{
	fd_set readSet;
	FD_ZERO(&readSet);
	FD_SET(m_socket, &readSet);
	ClientPtr client;

	if( select(m_socket, &readSet, NULL, NULL, &m_timeout) == 1)
	{
		client.reset( new Client( *this ) );
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

void ServerCommunicationManager::StoreClient( ClientPtr& client  )
{
	std::lock_guard<std::mutex> lock( m_clientsM );
	Clients::iterator it = std::find( m_clients.begin(), m_clients.end(), client );
	if( it !=  m_clients.end() )
	{
		throw std::runtime_error( "Client " + Log::AddrToStr( client->addr ) + " already stored " );
	}
	Log::Add( "Store client: " + Log::AddrToStr( client->addr ) );
	m_clients.push_back( client );
}

void ServerCommunicationManager::RemoveClient( const ClientPtr& client)
{
	std::lock_guard<std::mutex> lock( m_clientsM );
	Clients::iterator it = std::find( m_clients.begin(), m_clients.end(), client );
	if( it !=  m_clients.end() )
	{
		std::string addr =  Log::AddrToStr( (*it)->addr );
		Log::Add( "Remove client: " + addr );
		m_server.UnregisterNode( addr );
		m_clients.erase( it );
		Log::Add( "Client Removed: " + addr );
	}
	else
	{
		Log::Add( "Client: " + Log::AddrToStr( client->addr ) +" not found" );
	}
}

Client& ServerCommunicationManager::GetClient( const std::string &addr )
{
	std::lock_guard<std::mutex> lock( m_clientsM );
	Clients::iterator it;
	for( it = m_clients.begin(); it != m_clients.end(); ++it )
	{
		if ( Log::AddrToStr( (*it)->addr ) == addr )
		{
			break;
		}
	}
	if ( it == m_clients.end() )
	{
		throw( std::runtime_error( "Client: " + addr + "  not found!" ) );
	}
	return *it->get();
}

void ServerCommunicationManager::ListenSocketThread( ServerCommunicationManager &parent )
{
	Log::Add( "Start listen thread" );
	try
	{
		parent.ListenSocket();
	}
	catch( std::exception &exc )
	{
		Log::AddException( "Listen thread", exc );
	}
	Log::Add( "End listen thread" );
}

void ServerCommunicationManager::ListenSocket()
{
	while ( m_run )
	{
		ClientPtr client = CreateInputConn();
		if ( client.get() )
		{
			StoreClient( client );
			//Log::Add( "Start handler thread for client: " + Log::AddrToStr(client->addr) );
			client->thread.reset( new std::thread( ServerCommunicationManager::DataHandlerThread, client ) );
		}
	}
}

void ServerCommunicationManager::DataHandlerThread( ClientPtr client )
{
	std::string addr = Log::AddrToStr( client->addr );
	Log::Add( "Connected from " + addr );
	try
	{
		ReadSocket( client->socket, client->manager, addr );
	}
	catch( std::exception &exc )
	{
		Log::AddException( "Client " + addr, exc );
	}
	Log::Add( "Disconnected from " + addr );
	client->manager.RemoveClient( client );
}

void ServerCommunicationManager::CloseAdditionalThreads()
{
	for ( Clients::iterator iter = m_clients.begin(); iter != m_clients.end(); iter++ )
	{
		 (*iter)->thread->join();
	}
}
