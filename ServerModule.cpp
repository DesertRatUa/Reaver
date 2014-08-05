/*
 * ServerModule.cpp
 *
 *  Created on: 13 черв. 2014
 *      Author: maximm
 */

#include "ServerModule.h"
#include "Log.h"
#include <windows.h>

ServerModule::ServerModule( Config &config, ArgumentsMap &arguments ) : Module( config, arguments )
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
}

void ServerModule::Run()
{
	Log::Add( "Run server module" );
	unsigned port = 2222;
	std::string ip = "*";

	ParseIp( m_arguments("address").m_value, ip, port );

	m_connection.Listen( ip, port );

	m_signal.Wait();

	m_connection.Close();
	Log::Add( "Stop server module" );
}
