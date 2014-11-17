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
#include "ClientMessageProcessor.h"

ClientCommunicationManagerInterface *ClientMessageProcessor::m_communication(NULL);
ClientModule *ClientMessageProcessor::m_parent(NULL);

ClientMessageProcessor::ClientMessageProcessor( ClientModule &parent, ClientCommunicationManagerInterface &communication )
{
	m_parent = &parent;
	m_communication = &communication;
}

ClientMessageProcessor::~ClientMessageProcessor()
{
}

ClientMessageProcessorInterface::ClientMessageProcessorInterface()
{
}

ClientMessageProcessorInterface::~ClientMessageProcessorInterface()
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
	assert( mess.task.get() );
	m_parent->TaskRequest( mess.task );
}

void ClientMessageProcessor::SendEchoMessage( const std::string& message )
{
	assert( m_parent );
	EchoMessage mess( message );
	m_communication->SendRequest( mess );
}

void ClientMessageProcessor::SendRegisterMessage()
{
	assert( m_parent );
	RegisterMessage mess(4);
	m_communication->SendRequest( mess );
}

void ClientMessageProcessor::SendTaskMessage( const unsigned long time, TaskPtr &task )
{
	assert( m_parent );
	TaskMessage mess( time, task );
	m_communication->SendRespond( mess );
}
