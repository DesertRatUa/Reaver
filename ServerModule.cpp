/*
 * ServerModule.cpp
 *
 *  Created on: 13 черв. 2014
 *      Author: maximm
 */

#include "ServerModule.h"
#include "Log.h"
#include <windows.h>
#include "Tasks/TestTask.h"

ServerModule::ServerModule( Config &config, ArgumentsMap &arguments ) :
	Module( config, arguments ), m_connection( *this, m_processor, m_run ), m_processor(this),
	m_run(false), m_signal( m_run ), m_planner( m_nodes )
{
}

ServerModule::~ServerModule()
{
}

void ServerModule::Init()
{
	Log::SetName( "Server" );
	Log::Add( "Init server module" );
	m_signal.Init();
	m_connection.Init();
	m_processor.Init();
	m_nodes.Init();
	m_planner.Init();
}

void ServerModule::Run()
{
	Log::Add( "Run server module" );
	unsigned port = 2222;
	std::string ip = "*";

	ParseIp( m_arguments("address").m_value, ip, port );

	try
	{
		m_connection.Listen( ip, port );
		m_planner.Run();
		m_taskPlanner.reset( new std::thread( ServerModule::TaskPlannerThread, std::ref( *this ) ) );
		m_signal.Wait();
	}
	catch ( std::exception &exc )
	{
		Log::AddException( "ServerModule", exc );
	}

	Stop();
	m_planner.Stop();
	m_taskPlanner->join();
	m_connection.Close();
	Log::Add( "Stop server module" );
}

void ServerModule::Stop()
{
	m_run = false;
}

void ServerModule::TaskPlannerThread ( ServerModule &parent )
{
	Log::Add( "Start task add thread" );
	try
	{
		parent._TaskPlanner();
	}
	catch( std::exception &exc )
	{
		Log::AddException( "Task planner thread", exc );
	}
	Log::Add( "Stop task add thread" );
}

void ServerModule::_TaskPlanner()
{
	unsigned i = 0;
	while ( m_run )
	{
		++i;
		Sleep( 100 );
		if ( i >= 100 )
		{
			TaskPtr task( new TestTask( 0, 999999, 80000 ) );
			m_planner.AddTask( task, m_nodes.GetFreeThreadsNum() );
			i = 0;
		}
	}
}

void ServerModule::RegisterNode( const std::string& addr, const unsigned threadNum )
{
	try
	{
		m_nodes.RegisterNode( addr, threadNum, m_processor );
		m_processor.SendRegisterMessage( addr, NULL );
	}
	catch (std::exception &exc)
	{
		Log::AddException( "Server module::RegisterNode", exc );
		std::string error( exc.what() );
		m_processor.SendRegisterMessage( addr, &error );
	}
}

void ServerModule::UnregisterNode( const std::string& addr )
{
	try
	{
		m_nodes.UnregisterNode( addr );
	}
	catch (std::exception &exc)
	{
		Log::AddException( "Server module::UnregisterNode", exc );
	}
}

void ServerModule::TaskRespond( const std::string& addr, const TaskPtr &task )
{
	try
	{
		m_nodes.TaskComplete( addr, task );
		if ( task->isDone() )
		{
			m_planner.TaskComplete( task );
		}
	}
	catch (std::exception &exc)
	{
		Log::AddException( "ServerModule", exc );
	}
}
