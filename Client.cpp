/*
 * Client.cpp
 *
 *  Created on: 01 ���. 2014 �.
 *      Author: maximm
 */

#include "Client.h"
#include "Log.h"

Client::Client( CommunicationServer *Manager ) : manager( Manager ), socket( 0 )
{
}

Client::~Client()
{
	Log::Add( "Destroy client: " + Log::AddrToStr( addr ) );
}

bool Client::operator==( const Client &client ) const
{
	return inet_ntoa(addr.sin_addr) == inet_ntoa(client.addr.sin_addr) && addr.sin_port == client.addr.sin_port;
}

void  Client::Send( const std::string& message )
{
	send( socket, message.c_str(), message.length(), 0);
}