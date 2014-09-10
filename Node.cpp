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

Node::Node( const std::string &addr, const unsigned threadNum, ServerMessageProcessor &manager ) : m_busy( false ), m_addr( addr ), m_proccessor( manager ), m_threads(0), m_threadsLimit( threadNum )
{
}

Node::~Node()
{
}

bool Node::isBusy() const
{
	return m_busy;
}

bool Node::isThreadsAvalible() const
{
	return ( m_threadsLimit - m_threads ) >= 1;
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
	++m_threads;
	Log::Add( "Task: " + Log::UnsignedToStr( task->GetID() ) + " send to " + m_addr + " Avalible threads: " + Log::UnsignedToStr( m_threadsLimit - m_threads ) );
	m_proccessor.SendTaskMessage( m_addr, task );
}

void Node::TaskComplete()
{
	Log::Add( "Node: " + m_addr + " complete job" );
	m_busy = false;
	--m_threads;
}
