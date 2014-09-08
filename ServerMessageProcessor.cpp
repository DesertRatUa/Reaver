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
#include "Tasks/Task.h"

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
	RegisterProcessor( 2, &ServerMessageProcessor::RecieveRegisterMessage );
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

void ServerMessageProcessor::SendTaskMessage( const std::string &addr, Task &task )
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
	m_parent->RegisterNode( addr );
}

void ServerMessageProcessor::RecieveTaskMessage( const tinyxml2::XMLDocument& doc, const std::string& addr )
{
	assert( m_parent );
	TaskMessage mess;
	mess.DeserializeRespond( doc );
	Log::Add( "Recived task respond. Time spend: " +Log::IntToStr( mess.SpendTime ) + " ms" );
	assert( mess.task.get() );
	m_parent->TaskRespond( addr, *mess.task );
}
