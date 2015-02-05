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
	m_run = false;
	if ( m_mainThread.get() )
	{
		m_mainThread->join();
		m_mainThread.reset( NULL );
	}
	std::lock_guard<std::mutex> lock(m_mut);
	for( ThreadDataPtrs::iterator iter = m_threads.begin(); iter != m_threads.end(); ++iter )
	{
		ThreadDataPtr &ptr = *iter;
		if( !ptr->m_thread.get() )
		{
			Log::Add( "Null pointer to thread" );
			continue;
		}

		std::thread &thread = *ptr->m_thread;
		if ( !thread.joinable() )
		{
			Log::Add( "Thread is not joinabled" );
			continue;
		}
		thread.join();
	}
	m_threads.clear();
}

void ClientTaskPlanner::AddTask( TaskPtr &task )
{
	assert( task.get() );
	std::lock_guard<std::mutex> lock(m_mut);
	m_tasks.push_back( task );
	Log::Add( "Task added: " + Log::IntToStr( task->GetID() ) + ". Total tasks: " + Log::IntToStr( m_tasks.size() ) );
}

void ClientTaskPlanner::ThreadMain( ClientTaskPlanner &parent )
{
	Log::Add( "Start TaskPlanner thread" );
	parent.MainSequence();
	Log::Add( "Stop TaskPlanner thread. Total threads: " + Log::IntToStr( parent.m_tasks.size() ) );
}

void ClientTaskPlanner::ThreadTask( ThreadData *data )
{
	assert( data );
	assert( data->m_task.get() );
	assert( data->m_parent );
	TaskPtr &task = data->m_task;
	Log::Add( "Start task thread for taskId: " + Log::IntToStr( task->GetID() ) );
	unsigned respondTime = GetTickCount();
	task->Process();
	data->m_parent->SendTaskMessage( GetTickCount() - respondTime, task );
	Log::Add( "Stop task thread for taskId: " + Log::IntToStr( task->GetID() ) );
	data->m_done = true;
}

void ClientTaskPlanner::SendTaskMessage( const unsigned long time, TaskPtr &task )
{
	m_processor.SendTaskMessage( time, task );
}

void ClientTaskPlanner::MainSequence()
{
	while ( m_run )
	{
		Sleep(100);
		std::lock_guard<std::mutex> lock(m_mut);
		while ( m_tasks.size() > 0 && m_threads.size() < m_threadNums )
		{
			m_threads.push_back( ThreadDataPtr( new ThreadData( *this ) ) );
			ThreadData *thread = &( *m_threads.back() );

			thread->m_task = m_tasks.front();
			m_tasks.pop_front();

			thread->m_thread.reset( new std::thread( ClientTaskPlanner::ThreadTask, thread ) );
		}
		if ( m_threads.size() < m_threadNums && m_tasks.size() == 0 )
		{
			m_processor.SendRequesTaskMessage( m_threadNums - m_threads.size() );
		}
		for( ThreadDataPtrs::iterator iter = m_threads.begin(); iter != m_threads.end(); )
		{
			ThreadDataPtr &ptr = *iter;
			if ( ptr->m_done )
			{
				Log::Add( "Delete" );
				if( ptr->m_thread.get() )
				{
					std::thread &thread = *ptr->m_thread;
					Log::Add( "Point G" );
					if ( thread.joinable() )
					{
						Log::Add( "Join" );
						thread.join();
					}
					else
					{
						Log::Add( "Thread is not joinabled" );
					}
				}
				else
				{
					Log::Add( "Null pointer to thread" );
				}
				iter = m_threads.erase(iter);
				Log::Add( "Delete complete" );
			}
			else
			{
				++iter;
			}
		}
	}
}

ClientTaskPlanner::ThreadData::ThreadData( ClientTaskPlanner &Parent ) :
		m_done(false), m_parent(&Parent)
{
}
