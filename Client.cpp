/*
 * Client.cpp
 *
 *  Created on: 01 рту. 2014 у.
 *      Author: maximm
 */

#include "Client.h"

Client::Client( CommunicationServer *Manager ) : manager( Manager ), socket( 0 )
{
}

Client::~Client()
{
}

bool Client::operator==( const Client &client ) const
{
	return inet_ntoa(addr.sin_addr) == inet_ntoa(client.addr.sin_addr) && addr.sin_port == client.addr.sin_port;
}
