/*
 * CommunicationClient.cpp
 *
 *  Created on: 23 лип. 2014
 *      Author: maximm
 */

#include "CommunicationClient.h"
#include "Log.h"

CommunicationClient::CommunicationClient()
{
}

CommunicationClient::~CommunicationClient()
{
}

void CommunicationClient::Connect( const std::string &addr, const unsigned port )
{
	Log::Add( "Try connect to " + addr + ":" + Log::IntToStr( port ) );

	unsigned long remote = inet_addr( addr.c_str() );
	hostent* host = gethostbyaddr( (char*) &remote, 4, AF_INET );

	if ( !host )
	{
		Log::Add( "Failed get host by address" );
		return;
	}

	memcpy( &m_address.sin_addr, host->h_addr, host->h_length );
	m_address.sin_family = host->h_addrtype;
	m_address.sin_port = htons(port);

	if ( connect(m_socket, (sockaddr*) &m_address, sizeof(m_address) ) == SOCKET_ERROR )
	{
		Log::Add( "Failed to connect" );
		return;
	}

	u_long NonBlock = 1;
	if ( ioctlsocket( m_socket, FIONBIO, &NonBlock ) == SOCKET_ERROR )
	{
		Log::Add( "Setting non blocking failed" );
	}

	Log::Add( "Connected to " + addr + ":" + Log::IntToStr( port ) );

	pthread_create( &m_mainThread, NULL, &DataHandlerThr, (void*)this );
}

void *CommunicationClient::DataHandlerThr( void *arg )
{
	if ( !arg )
	{
		Log::Add( "Null pointer in handler thread" );
		return NULL;
	}
	Log::Add( "Start handler thread" );
	CommunicationClient *manager = (CommunicationClient*) arg;

	ReadSocket( manager->m_socket, manager->m_run );

	Log::Add( "End handler thread" );
	pthread_exit(NULL);
	return NULL;
}

void CommunicationClient::Send( const std::string &message )
{
		send( m_socket, message.c_str(), message.length(), 0);
}
