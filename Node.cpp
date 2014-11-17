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

Node::Node( const std::string &addr, const unsigned threadNum, ServerMessageProcessorInterface &manager ) :
	m_addr( addr ), m_proccessor( manager ), m_threads(0), m_threadsLimit( threadNum )
{
}

Node::~Node()
{
}

unsigned Node::GetFreeThreadsNum() const
{
	return m_threadsLimit - m_threads;
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
	m_addr = node.m_addr;
	m_proccessor = node.m_proccessor;
	return *this;
}

void Node::SendTask( TaskPtr& task ) throw ( std::exception )
{
	if ( m_threads >= m_threadsLimit  )
	{
		throw std::runtime_error( "No free threads on node: " + m_addr );
	}
	++m_threads;
	Log::Add( "Task: " + Log::IntToStr( task->GetID() ) + " send to " + m_addr + " Avalible threads: " + Log::IntToStr( m_threadsLimit - m_threads ) );
	m_proccessor.SendTaskMessage( m_addr, task );
}

void Node::TaskComplete() throw ( std::exception )
{
	Log::Add( "Node: " + m_addr + " complete job" );
	if ( m_threads == 0 )
	{
		throw std::runtime_error( "No used threads on node: " + m_addr );
	}
	--m_threads;
}
