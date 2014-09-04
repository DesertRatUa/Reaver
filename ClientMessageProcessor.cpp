/*
 * ClientMessageProcessor.cpp
 *
 *  Created on: 08 рту. 2014 у.
 *      Author: maximm
 */

#include "ClientMessageProcessor.h"
#include "ClientModule.h"
#include "Log.h"

#include "Messages/RegisterMessage.h"
#include "Messages/EchoMessage.h"
#include "Messages/TaskMessage.h"

ClientModule *ClientMessageProcessor::m_parent(NULL);

ClientMessageProcessor::ClientMessageProcessor( ClientModule *parent  )
{
	m_parent = parent;
}

ClientMessageProcessor::~ClientMessageProcessor()
{
}

void ClientMessageProcessor::Init()
{
	RegisterProcessor( 1, &ClientMessageProcessor::RecieveEchoMessage );
	RegisterProcessor( 2, &ClientMessageProcessor::RecieveRegisterMessage );
	RegisterProcessor( 3, &ClientMessageProcessor::ReciveTaskMessage );
}

void ClientMessageProcessor::RecieveEchoMessage( const tinyxml2::XMLDocument& doc, const std::string& addr )
{
	assert( m_parent );
	EchoMessage message;
	message.DeserializeRespond( doc );
	Log::Add( "Echo message return: " + message.Text );
	m_parent->ConnectionRespond();
}

void ClientMessageProcessor::RecieveRegisterMessage( const tinyxml2::XMLDocument& doc, const std::string& addr )
{
	assert( m_parent );
	RegisterMessage mess;
	mess.DeserializeRespond( doc );
	Log::Add( "Client registered with ID: " + mess.ClientId );
	m_parent->RegisterRespond();
}

void ClientMessageProcessor::ReciveTaskMessage( const tinyxml2::XMLDocument& doc, const std::string& addr )
{
	assert( m_parent );
	TaskMessage mess;
	mess.DeserializeReqest( doc );
	Log::Add( "Recive Task" );
	m_parent->TaskRequest();
}

void ClientMessageProcessor::SendEchoMessage( const std::string& message )
{
	EchoMessage mess( message );
	m_parent->m_connection.SendRequest( mess );
}

void ClientMessageProcessor::SendRegisterMessage()
{
	RegisterMessage mess;
	m_parent->m_connection.SendRequest( mess );
}

void ClientMessageProcessor::SendTaskMessage( const unsigned time )
{
	TaskMessage mess( time );
	m_parent->m_connection.SendRespond( mess );
}
