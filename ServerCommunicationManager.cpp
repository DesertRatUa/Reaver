/*
 * CommunicationServer.cpp
 *
 *  Created on: 23 ���. 2014
 *      Author: maximm
 */

#include "ServerCommunicationManager.h"
#include "Log.h"
#include <algorithm>
#include "MessageProcessor.h"
#include "ServerModule.h"
#include <thread>

ServerCommunicationManager::ServerCommunicationManager( ServerModule &server, MessageProcessor &processor, bool &isRun  ) :
	CommunicationManager( processor, isRun ), m_server( server ), m_haveDisconnected( false )
{
}

ServerCommunicationManager::~ServerCommunicationManager()
{
}

void ServerCommunicationManager::Init()
{
	CommunicationManager::Init();
	m_clients.Init();
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
		client.reset( new Client() );
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

Client& ServerCommunicationManager::GetClient( const std::string &addr )
{
	return m_clients.Get( addr );
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
			m_clients.Add( client );
			//Log::Add( "Start handler thread for client: " + Log::AddrToStr(client->addr) );
			client->thread.reset( new std::thread( ServerCommunicationManager::DataHandlerThread, client, std::ref( *this ) ) );
		}
		if ( m_haveDisconnected )
		{
			RemoveDisconnected();
		}
	}
}

void ServerCommunicationManager::DataHandlerThread( ClientPtr client, ServerCommunicationManager &parent )
{
	std::string addr = Log::AddrToStr( client->addr );
	Log::Add( "Connected from " + addr );
	try
	{
		ReadSocket( client->socket, parent, addr );
	}
	catch( std::exception &exc )
	{
		Log::AddException( "Client " + addr, exc );
	}
	Log::Add( "Disconnected from " + addr );
	parent.m_server.UnregisterNode( addr );
	client->Disconnect();
	parent.ClientDisconnect();
}

void ServerCommunicationManager::CloseAdditionalThreads()
{
	m_clients.Clear();
}

void ServerCommunicationManager::ClientDisconnect()
{
	std::lock_guard<std::mutex> lock( m_discon );
	m_haveDisconnected = true;
}

void ServerCommunicationManager::RemoveDisconnected()
{
	std::lock_guard<std::mutex> lock( m_discon );
	m_clients.RemoveDisconnected();
	m_haveDisconnected = false;
}
