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
#include "ClientMessageProcessor.h"

ClientTaskPlanner::ClientTaskPlanner( ClientMessageProcessorInterface &processor, unsigned ThreadNums ) :
	m_threadNums( ThreadNums ), m_run( false ), m_processor( processor )
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
	m_mainThread.reset( new std::thread(
			ClientTaskPlanner::ThreadMain, std::ref( *this ) ) );
}

void ClientTaskPlanner::Stop()
{
	Log::Add("1");
	m_run = false;
	if ( m_mainThread.get() )
	{
		m_mainThread->join();
		m_mainThread.reset( NULL );
	}
	Log::Add("2");
	std::lock_guard<std::mutex> lock(m_mut);
	Log::Add("3");
	for( TaskThrds::iterator iter = m_threads.begin(); iter != m_threads.end(); ++iter )
	{
		Log::Add("4");
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
	Log::Add("5");
	m_threads.clear();
}

void ClientTaskPlanner::AddTask( TaskPtr &task )
{
	std::lock_guard<std::mutex> lock(m_mut);
	//Log::Add( Log::IntToStr( unsigned( task.use_count() ) ) );
	m_tasks.push_back( task );
	//Log::Add( Log::IntToStr( unsigned( task.use_count() ) ) );
}

void ClientTaskPlanner::ThreadMain( ClientTaskPlanner &parent )
{
	Log::Add( "Start TaskPlanner thread" );
	parent.MainSequence();
	Log::Add( "Stop TaskPlanner thread" );
}

void ClientTaskPlanner::ThreadTask( TaskThrd *thread )
{
	Log::Add( "Start task" );
	assert( thread->task.get() );
	assert( thread->parent );
	Log::Add( "Start task thread for taskId: " + Log::IntToStr( thread->task->GetID() ) );
	//thread->parent->TaskProcess( thread->task );
	Log::Add( "Stop task thread for taskId: " + Log::IntToStr( thread->task->GetID() ) );
	thread->Done = true;
	Log::Add( "Stop task" );
}

void ClientTaskPlanner::TaskProcess( TaskPtr &task )
{
	unsigned respondTime = GetTickCount();
	task->Process();
	m_processor.SendTaskMessage( GetTickCount() - respondTime, task );
}

void ClientTaskPlanner::MainSequence()
{
	while ( m_run )
	{
		if ( m_tasks.size() > 0 && m_threads.size() < m_threadNums )
		{
			std::lock_guard<std::mutex> lock(m_mut);
			m_threads.push_back( TaskThrd( *this ) );
			TaskThrd &thread = m_threads.back();

			Log::Add( Log::IntToStr( unsigned( thread.task.use_count() ) ) );
			thread.task = m_tasks.front();
			m_tasks.pop_front();
			assert( thread.task.get() );
			Log::Add( Log::IntToStr( unsigned( thread.task.use_count() ) ) );
			thread.thread.reset( new std::thread( ClientTaskPlanner::ThreadTask, &thread ) ) ;
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
				Log::Add( "Delete" );

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
				iter = m_threads.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
}

ClientTaskPlanner::TaskThrd::TaskThrd( ClientTaskPlanner &Parent ) : Done(false), parent(&Parent)
{
}
