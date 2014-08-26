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

	pthread_create( &m_mainThread, NULL, &DataHandlerThr, (void*)this );
}

void *ClientCommunicationManager::DataHandlerThr( void *arg )
{
	assert( arg );
	Log::Add( "Start handler thread" );
	ClientCommunicationManager *manager = (ClientCommunicationManager*) arg;

	ReadSocket( manager->m_socket, manager, Log::AddrToStr( manager->m_address ) );

	Log::Add( "End handler thread" );
	manager->m_run = false;
	pthread_exit(NULL);
	return NULL;
}

void ClientCommunicationManager::Send( const std::string &message )
{
	send( m_socket, message.c_str(), message.length(), 0);
}

void ClientCommunicationManager::Send( const Message &message )
{
	Send( message.SerializeReqest() );
}
