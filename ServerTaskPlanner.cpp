/*
 * TaskPlanner.cpp
 *
 *  Created on: 03 но€б. 2014 г.
 *      Author: maximm
 */

#include "ServerTaskPlanner.h"
#include "NodesMap.h"
#include "Log.h"
#include <windows.h>

ServerTaskPlanner::ServerTaskPlanner(  NodesMap &map) :
	m_taskCount(0), m_run(false), m_nodes( map )
{
}

ServerTaskPlanner::~ServerTaskPlanner()
{
}

void ServerTaskPlanner::Init()
{
}

void ServerTaskPlanner::Run()
{
	m_run = true;
	m_thread.reset( new std::thread( ServerTaskPlanner::Thread, std::ref( *this ) ) );
}

void ServerTaskPlanner::Stop()
{
	m_run = false;
	m_thread->join();
}

void ServerTaskPlanner::Thread( ServerTaskPlanner &parent )
{
	Log::Add( "Start TaskPlanner thread" );
	parent.ThreadRun();
	Log::Add( "Stop TaskPlanner thread" );
}

void ServerTaskPlanner::ThreadRun()
{
	Node *node = NULL;
	while ( m_run )
	{
		if ( m_tasks.size() != 0 )
		{
			node = m_nodes.GetFreeNode();
			if ( node != NULL )
			{
				std::lock_guard<std::mutex> lock( m_mut );
				node->SendTask( m_tasks.front() );
				m_tasks.pop_front();
				continue;
			}
		}
		if ( m_run )
		{
			Sleep(100);
		}
	}
}

void ServerTaskPlanner::AddTask( const TaskPtr &task, const unsigned threadsNum )
{
	Tasks tasks = task->SeperateTask( threadsNum, ++m_taskCount );
	std::lock_guard<std::mutex> lock( m_mut );
	Log::Add( "Add " + Log::IntToStr( unsigned( tasks.size() ) ) + " tasks" );
	m_tasks.insert( m_tasks.end(), tasks.begin(), tasks.end() );
}

void ServerTaskPlanner::TaskComplete( const TaskPtr &task )
{
	const unsigned &id = task->GetPlannerID();
	std::lock_guard<std::mutex> lock( m_mut );
	for ( Tasks::iterator iter = m_tasks.begin(); iter !=  m_tasks.end(); )
	{
		if ( (*iter)->GetPlannerID() == id )
		{
			iter = m_tasks.erase( iter );
		}
		else
		{
			++iter;
		}
	}
}
