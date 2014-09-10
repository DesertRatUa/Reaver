/*
 * ServerModule.cpp
 *
 *  Created on: 13 черв. 2014
 *      Author: maximm
 */

#include "ServerModule.h"
#include "Log.h"
#include <windows.h>
#include <thread>

ServerModule::ServerModule( Config &config, ArgumentsMap &arguments ) : Module( config, arguments ), m_connection( *this, m_processor, m_run ), m_processor(this), m_run(false), m_signal( m_run ), m_mut(0), m_nodes( m_processor )
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
	pthread_mutex_init( &m_mut, NULL );
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
		pthread_create( &m_taskPlanner, NULL, ServerModule::TaskPlannerThread, this );
		m_signal.Wait();
	}
	catch ( std::exception &exc )
	{
		Log::Add( "ServerModule exception: " + std::string( exc.what() ) );
	}

	m_connection.Close();
	Log::Add( "Stop server module" );
}

void* ServerModule::TaskPlannerThread ( void *arg )
{
	assert( arg );
	Log::Add( "Start task planner thread" );
	ServerModule *module = (ServerModule*)arg;
	module->TaskPlanner();
	Log::Add( "Stop task planner thread" );
	return NULL;
}

void ServerModule::TaskPlanner()
{
	while ( m_run )
	{
		Node *node = m_nodes.GetFreeNode();
		if ( node )
		{
			TaskPtr task( new TestTask( 0, 99999, 3496675 ) );
			node->SendTask( task );
		}
		else
		{
			Sleep( 1000 );
		}
	}
}

void ServerModule::RegisterNode( const std::string& addr, const unsigned threadNum )
{
	m_nodes.RegisterNode( addr, threadNum );
}

void ServerModule::UnregisterNode( const std::string& addr )
{
	m_nodes.UnregisterNode( addr );
}

void ServerModule::TaskRespond( const std::string& addr, Task &task )
{
	m_nodes.TaskComplete( addr );
}
