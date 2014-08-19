/*
 * ServerMessageProcessor.cpp
 *
 *  Created on: 08 рту. 2014 у.
 *      Author: maximm
 */

#include "ServerMessageProcessor.h"
#include "ServerModule.h"
#include "Log.h"
#include "Messages/EchoMessage.h"

ServerModule *ServerMessageProcessor::m_parent(NULL);

ServerMessageProcessor::ServerMessageProcessor( ServerModule *parent )
{
	m_parent = parent;
}

ServerMessageProcessor::~ServerMessageProcessor()
{
}

void ServerMessageProcessor::Init()
{
	RegisterProcessor( 1, &ServerMessageProcessor::RecieveEchoMessage );
}

void ServerMessageProcessor::RecieveEchoMessage( const tinyxml2::XMLDocument& doc, const std::string& addr )
{
	assert( m_parent );
	EchoMessage message;
	message.Deserialize( doc );
	Log::Add( "Recived echo message: " + message.Text + " respond" );
	m_parent->m_connection.GetClient( addr ).Send( message );
}
