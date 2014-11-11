/*
 * ClientTaskPlanner.cpp
 *
 *  Created on: 10 но€б. 2014 г.
 *      Author: maximm
 */

#include <ClientTaskPlanner.h>
#include "Log.h"
#include <windows.h>
#include <assert.h>

ClientTaskPlanner::ClientTaskPlanner( unsigned ThreadNums ) :
	m_threadNums( ThreadNums ), m_run( false )
{
}

ClientTaskPlanner::~ClientTaskPlanner()
{
	Stop();
}

void ClientTaskPlanner::Init()
{
	m_threads.reserve(m_threadNums);
}

void ClientTaskPlanner::Run()
{
	m_run = true;
	m_mainThread.reset( new std::thread( ClientTaskPlanner::Thread, std::ref( *this ) ) );
}

void ClientTaskPlanner::Stop()
{
	m_run = false;
	if ( m_mainThread.get() )
	{
		m_mainThread->join();
		m_mainThread.reset( NULL );
	}
	std::lock_guard<std::mutex> lock(m_mut);
	for( TaskThrds::iterator iter = m_threads.begin(); iter != m_threads.end(); ++iter )
	{
		if( !iter->thread.get() )
		{
			Log::Add( "Null pointer to thread" );
			continue;
		}
		if ( !iter->thread->joinable() )
		{
			Log::Add( "Thread is not joinabled" );
			continue;
		}
		iter->thread->join();
	}
	m_threads.clear();
}

void ClientTaskPlanner::AddTask( TaskPtr &task )
{
	std::lock_guard<std::mutex> lock(m_mut);
	m_tasks.push_back( task );
}

void ClientTaskPlanner::Thread( ClientTaskPlanner &parent )
{
	Log::Add( "Start TaskPlanner thread" );
	parent.TaskPlanner();
	Log::Add( "Stop TaskPlanner thread" );
}

void ClientTaskPlanner::TaskThread( TaskPtr task, TaskThrd &thread )
{
	Log::Add( "Start task thread for taskId: " + Log::IntToStr( task->GetID() ) );
	unsigned respondTime = GetTickCount();
	task->Process();
	Log::Add( "Stop task thread for taskId: " + Log::IntToStr( task->GetID() ) );
	thread.Done = true;
	//processor.SendTaskMessage( GetTickCount() - respondTime, task );
}

void ClientTaskPlanner::TaskPlanner()
{
	while ( m_run )
	{
		if ( m_tasks.size() > 0 && m_threads.size() < m_threadNums )
		{
			std::lock_guard<std::mutex> lock(m_mut);
			m_threads.push_back( TaskThrd() );
			TaskThrd &thread = m_threads.back();
			thread.thread.reset( new std::thread( ClientTaskPlanner::TaskThread, m_tasks.front(), std::ref( thread ) ) ) ;
			m_tasks.pop_front();
		}
		else
		{
			Sleep(100);
		}
		std::lock_guard<std::mutex> lock(m_mut);
		for( TaskThrds::iterator iter = m_threads.begin(); iter != m_threads.end(); )
		{
			if ( iter->Done )
			{
				iter->thread->join();
				iter = m_threads.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
}

ClientTaskPlanner::TaskThrd::TaskThrd() : Done(false)
{
}
