/*
 * Node.cpp
 *
 *  Created on: 26 рту. 2014 у.
 *      Author: maximm
 */

#include <Node.h>
#include "Client.h"
#include "ServerMessageProcessor.h"
#include "Log.h"
#include "Tasks/Task.h"
#include <algorithm>

Node::Node( const Client &client, const unsigned threadNum, ServerMessageProcessorInterface &manager ) :
	m_client( &client ), m_proccessor( &manager ), m_mut( new std::mutex() ), m_threads(threadNum)
{
}

Node::~Node()
{
}

std::string Node::GetAddr() const
{
	return m_client->GetAddr();
}

unsigned Node::GetThreadsCount() const
{
	return m_threads;
}

bool Node::operator==( const Node& node ) const
{
	return GetAddr() == node.GetAddr();
}

bool Node::operator==( const std::string& addr ) const
{
	return GetAddr() == addr;
}

void Node::SendTask( const TaskPtr& task ) throw ( std::exception )
{
	std::lock_guard<std::mutex> lock( *m_mut );
	Log::Add( "Task: " + Log::IntToStr( task->GetID() ) + " send to " + GetAddr()  );
	m_proccessor->SendTaskMessage( *m_client, task );
}

void Node::TaskComplete( const TaskPtr& task ) throw ( std::exception )
{
	std::lock_guard<std::mutex> lock( *m_mut );
	Log::Add( "Node: " + GetAddr() + " complete job" );
}
