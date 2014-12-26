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

ServerTaskPlanner::ServerTaskPlanner() : m_taskCount(0)
{
}

ServerTaskPlanner::~ServerTaskPlanner()
{
}

void ServerTaskPlanner::Init()
{
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

TaskPtr ServerTaskPlanner::GetTask()
{
	TaskPtr ptr;
	std::lock_guard<std::mutex> lock( m_mut );
	if ( m_tasks.size() )
	{
		ptr = m_tasks.front();
		m_tasks.pop_front();
	}
	return ptr;
}
