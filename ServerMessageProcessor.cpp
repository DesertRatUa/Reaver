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
#include "Messages/TaskMessage.h"

#include "tinyxml2.h"

ServerModule *ServerMessageProcessor::m_parent(NULL);

ServerMessageProcessor::ServerMessageProcessor( ServerModule *parent )
{
	m_parent = parent;
}

ServerMessageProcessor::~ServerMessageProcessor()
{
}

ServerMessageProcessorInterface::ServerMessageProcessorInterface()
{
}

ServerMessageProcessorInterface::~ServerMessageProcessorInterface()
{
}

void ServerMessageProcessor::Init()
{
	RegisterProcessor( 1, &ServerMessageProcessor::RecieveEchoMessage );
	RegisterProcessor( 2, &ServerMessageProcessor::RecieveRegisterMessage );
	RegisterProcessor( 3, &ServerMessageProcessor::RecieveTaskMessage );
}

void ServerMessageProcessor::SendRegisterMessage( const std::string &addr, const std::string *error )
{
	RegisterMessage mess;
	if ( error )
	{
		mess.ErrorMsg = *error;
	}
	mess.ClientId = addr;
	m_parent->m_connection.GetClient( addr ).SendRespond( mess );
}

void ServerMessageProcessor::SendTaskMessage( const std::string &addr, const TaskPtr &task )
{
	TaskMessage mess(task);
	m_parent->m_connection.GetClient( addr ).SendRequest( mess );
}

void ServerMessageProcessor::RecieveEchoMessage( const tinyxml2::XMLDocument& doc, const std::string& addr )
{
	assert( m_parent );
	EchoMessage message;
	message.DeserializeReqest( doc );
	Log::Add( "Recived echo message: " + message.Text + " respond" );
	m_parent->m_connection.GetClient( addr ).SendRespond( message );
}

void ServerMessageProcessor::RecieveRegisterMessage( const tinyxml2::XMLDocument& doc, const std::string& addr )
{
	assert( m_parent );
	RegisterMessage mess;
	mess.DeserializeReqest( doc );
	Log::Add( "Recive register message: " + addr );
	m_parent->RegisterNode( addr, mess.ThreadNum );
}

void ServerMessageProcessor::RecieveTaskMessage( const tinyxml2::XMLDocument& doc, const std::string& addr )
{
	assert( m_parent );
	TaskMessage mess;
	mess.DeserializeRespond( doc );
	assert( mess.Task );
	Log::Add( "Recived task: " + Log::IntToStr( mess.Task->GetID() ) + " respond. Time spend: " +Log::IntToStr( mess.SpendTime ) + " ms" );
	assert( mess.Task.get() );
	m_parent->TaskRespond( addr, mess.Task );
}
