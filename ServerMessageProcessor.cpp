/*
 * ServerMessageProcessor.cpp
 *
 *  Created on: 08 ���. 2014 �.
 *      Author: maximm
 */

#include "ServerMessageProcessor.h"
#include "ServerModule.h"
#include "Log.h"
#include "Messages/EchoMessage.h"
#include "Messages/RegisterMessage.h"
#include "Messages/TaskMessage.h"
#include "Messages/RequestTaskMessage.h"

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
	RegisterProcessor( 4, &ServerMessageProcessor::RecieveRequesTaskMessage );
}

void ServerMessageProcessor::SendRegisterMessage( const Client &client, const std::string *error )
{
	RegisterMessage mess;
	if ( error )
	{
		mess.ErrorMsg = *error;
	}
	mess.ClientId = client.GetAddr();
	client.SendRespond( mess );
}

void ServerMessageProcessor::SendTaskMessage( const Client &client, const TaskPtr &task )
{
	TaskMessage mess(task);
	client.SendRequest( mess );
}

void ServerMessageProcessor::SendCancelTaskMessage( const Client &client, const unsigned plannerId )
{
	TaskMessage mess( true, plannerId );
	client.SendRequest( mess );
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
	if ( mess.Cancel )
	{
		Log::Add( "Task: " + Log::IntToStr( mess.Task->GetID() ) + "Canceled" );
	}
	else
	{
		assert( mess.Task.get() );
		m_parent->TaskRespond( addr, mess.Task );
	}
}

void ServerMessageProcessor::RecieveRequesTaskMessage( const tinyxml2::XMLDocument& doc, const std::string& addr )
{
	assert( m_parent );
	RequestTaskMessage mess;
	mess.DeserializeReqest( doc );
	m_parent->TaskRequest( addr, mess.m_threads );
}
