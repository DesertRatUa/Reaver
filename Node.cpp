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

Node::Node( const std::string &addr, const unsigned threadNum, ServerMessageProcessorInterface &manager ) :
	m_addr( addr ), m_proccessor( &manager ), m_threadsLimit( threadNum ), m_mut( new std::mutex() )
{
}

Node::~Node()
{
}

Node::ThreadData::ThreadData( unsigned long start, unsigned id ) : startTime(start), plannerID(id)
{
}

bool Node::ThreadData::operator==( const unsigned &id ) const
{
	return plannerID == id;
}

unsigned Node::GetFreeThreadsNum() const
{
	return m_threadsLimit - m_times.size();
}

bool Node::isThreadsAvalible() const
{
	return ( m_threadsLimit - m_times.size() ) >= 1;
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

void Node::SendTask( const TaskPtr& task ) throw ( std::exception )
{
	std::lock_guard<std::mutex> lock( *m_mut );
	int avalible = m_threadsLimit - m_times.size();
	if ( avalible <= 0  )
	{
		throw std::runtime_error( "No free threads on node: " + m_addr );
	}
	m_times.push_back( ThreadData( GetTickCount(), task->GetPlannerID() ) );
	Log::Add( "Task: " + Log::IntToStr( task->GetID() ) + " send to " + m_addr + " Avalible threads: " + Log::IntToStr( avalible ) );
	m_proccessor->SendTaskMessage( m_addr, task );
}

void Node::TaskComplete( const TaskPtr& task ) throw ( std::exception )
{
	std::lock_guard<std::mutex> lock( *m_mut );
	//Log::Add( "Node: " + m_addr + " complete job" );
	if ( m_times.size() == 0 )
	{
		throw std::runtime_error( "No used threads on node: " + m_addr );
	}
	TaskTimes::iterator iter = std::find( m_times.begin(), m_times.end(), task->GetPlannerID() );
	if( iter == m_times.end() )
	{
		throw std::runtime_error( "No time record for task: " + Log::IntToStr( task->GetPlannerID() ) );
	}
	m_times.erase( iter );
}

void Node::CheckForStaleTasks( const unsigned timeOut )
{
	std::lock_guard<std::mutex> lock( *m_mut );
	unsigned long time = GetTickCount();
	for ( TaskTimes::iterator iter = m_times.begin(); iter != m_times.end(); )
	{
		if ( time - iter->startTime >= timeOut )
		{
			Log::Add( "Delete stale task: " + Log::IntToStr( iter->plannerID ) );
			m_proccessor->SendCancelTaskMessage( m_addr, iter->plannerID );
			iter = m_times.erase( iter );
		}
		else
		{
			++iter;
		}
	}
}
