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
#include "Messages/RegisterMessage.h"

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

void ServerMessageProcessor::SendRegisterMessage( const std::string &addr, const unsigned id, const std::string *error )
{
	RegisterMessage mess;
	if ( error )
	{
		mess.ErrorMsg = *error;
	}
	mess.ClientId = id;
	m_parent->m_connection.GetClient( addr ).Send( mess );
}

void ServerMessageProcessor::RecieveEchoMessage( const tinyxml2::XMLDocument& doc, const std::string& addr )
{
	assert( m_parent );
	EchoMessage message;
	message.DeserializeReqest( doc );
	Log::Add( "Recived echo message: " + message.Text + " respond" );
	m_parent->m_connection.GetClient( addr ).Send( message );
}

void ServerMessageProcessor::RecieveRegisterMessage( const tinyxml2::XMLDocument& doc, const std::string& addr )
{
	assert( m_parent );
	RegisterMessage mess;
	mess.DeserializeReqest( doc );
	m_parent->RegisterNode( addr );
}
