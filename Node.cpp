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

Node::Node( const std::string &addr, ServerMessageProcessor &manager ) : m_busy( false ), m_addr( addr ), m_proccessor( manager )
{
}

Node::~Node()
{
}

bool Node::isBusy() const
{
	return m_busy;
}

std::string Node::GetID() const
{
	return m_addr;
}

bool Node::operator==( const Node& node ) const
{
	return GetID() == node.GetID();
}

bool Node::operator==( const std::string& addr ) const
{
	return m_addr == addr;
}

Node& Node::operator=(const Node& node )
{
	m_busy = node.m_busy;
	m_addr = node.m_addr;
	m_proccessor = node.m_proccessor;
	return *this;
}

void Node::SendTask( TaskPtr& task )
{
	m_busy = true;
	Log::Add( "Task: " + Log::UnsignedToStr( task->GetID() ) + " send to " + m_addr );
	m_proccessor.SendTaskMessage( m_addr, task );
}

void Node::TaskComplete()
{
	m_busy = false;
}
