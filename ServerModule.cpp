/*
 * ServerModule.cpp
 *
 *  Created on: 13 ����. 2014
 *      Author: maximm
 */

#include "ServerModule.h"
#include "Log.h"
#include <windows.h>

ServerModule::ServerModule( Config &config, ArgumentsMap &arguments ) : Module( config, arguments ), m_connection( m_processor, m_run ), m_processor(this), m_run(false), m_signal( m_run )
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

void ServerModule::EchoPrc( const std::string& message, const std::string& addr )
{

}
