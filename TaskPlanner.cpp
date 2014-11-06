/*
 * TaskPlanner.cpp
 *
 *  Created on: 03 но€б. 2014 г.
 *      Author: maximm
 */

#include <TaskPlanner.h>

TaskPlanner::TaskPlanner() : m_taskCount(0)
{
}

TaskPlanner::~TaskPlanner()
{
}

void TaskPlanner::Init()
{
}

void TaskPlanner::Run()
{
}

void TaskPlanner::AddTask( const TaskPtr &task, const unsigned threadsNum )
{
	Tasks tasks = task->SeperateTask( threadsNum, ++m_taskCount );
	std::lock_guard<std::mutex> lock( m_mut );
	m_tasks.insert( m_tasks.end(), tasks.begin(), tasks.end() );
}

void TaskPlanner::TaskComplete( const TaskPtr &task )
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
