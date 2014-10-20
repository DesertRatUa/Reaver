/*
 * CommunicationClient.cpp
 *
 *  Created on: 23 лип. 2014
 *      Author: maximm
 */

#include "ClientCommunicationManager.h"
#include "Log.h"
#include "Messages/Message.h"
#include <assert.h>
#include <thread>

ClientCommunicationManager::ClientCommunicationManager( MessageProcessor &processor, bool &isRun ) : CommunicationManager( processor, isRun )
{
}

ClientCommunicationManager::~ClientCommunicationManager()
{
}

void ClientCommunicationManager::Connect( const std::string &addr, const unsigned port ) throw(std::runtime_error)
{
	Log::Add( "Try connect to " + addr + ":" + Log::IntToStr( port ) );
	m_run = true;
	unsigned long remote = inet_addr( addr.c_str() );
	hostent* host = gethostbyaddr( (char*) &remote, 4, AF_INET );

	if ( !host )
	{
		throw(std::runtime_error( "Failed get host by address" ));
	}

	memcpy( &m_address.sin_addr, host->h_addr, host->h_length );
	m_address.sin_family = host->h_addrtype;
	m_address.sin_port = htons(port);

	if ( connect(m_socket, (sockaddr*) &m_address, sizeof(m_address) ) == SOCKET_ERROR )
	{
		throw(std::runtime_error( "Failed to connect" ));
	}

	u_long NonBlock = 1;
	if ( ioctlsocket( m_socket, FIONBIO, &NonBlock ) == SOCKET_ERROR )
	{
		throw(std::runtime_error( "Setting non blocking failed" ));
	}

	Log::Add( "Connected to " + addr + ":" + Log::IntToStr( port ) );

	m_mainThread.reset( new std::thread( DataHandlerThr, std::ref( *this ) ) );
}

void ClientCommunicationManager::DataHandlerThr( ClientCommunicationManager &parent )
{
	Log::Add( "Start handler thread" );
	ReadSocket( parent.m_socket, parent, Log::AddrToStr( parent.m_address ) );

	Log::Add( "End handler thread" );
	parent.m_run = false;
}

void ClientCommunicationManager::Send( const std::string &message )
{
	send( m_socket, message.c_str(), message.length(), 0);
}

void ClientCommunicationManager::SendRequest( const Message &message )
{
	Send( message.SerializeReqest() );
}

void ClientCommunicationManager::SendRespond( const Message &message )
{
	Send( message.SerializeRespond() );
}
