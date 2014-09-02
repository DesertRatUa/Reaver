/*
 * ServerModule.cpp
 *
 *  Created on: 13 черв. 2014
 *      Author: maximm
 */

#include "ServerModule.h"
#include "Log.h"
#include <windows.h>

ServerModule::ServerModule( Config &config, ArgumentsMap &arguments ) : Module( config, arguments ), m_connection( *this, m_processor, m_run ), m_processor(this), m_run(false), m_signal( m_run ), m_mut(0), m_nodesID(0)
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
		m_signal.Wait();
	}
	catch ( std::exception &exc )
	{
		Log::Add( "ServerModule exception: " + std::string( exc.what() ) );
	}

	m_connection.Close();
	Log::Add( "Stop server module" );
}

void ServerModule::RegisterNode( const std::string& addr )
{
	pthread_mutex_lock( &m_mut );

	Nodes::iterator iter = std::find( m_nodes.begin(), m_nodes.end(), addr );
	if ( iter == m_nodes.end() )
	{
		m_nodes.push_back( Node( m_connection.GetClient( addr ),  ++m_nodesID ) );
		m_processor.SendRegisterMessage( addr, NULL );
		Log::Add( "Node: " + addr + " registered" );
	}
	else
	{
		std::string error = "Node: " + addr + " already registered";
		Log::Add( error );
		m_processor.SendRegisterMessage( addr, &error );
	}

	pthread_mutex_unlock( &m_mut );
}

void ServerModule::UnregisterNode( const std::string& addr )
{
	pthread_mutex_lock( &m_mut );

	Nodes::iterator iter = std::find( m_nodes.begin(), m_nodes.end(), addr );
	if ( iter == m_nodes.end() )
	{
		Log::AddMessage( "Node: " + addr + " not registered" );
	}
	else
	{
		m_nodes.erase( iter );
	}
	pthread_mutex_unlock( &m_mut );
}
