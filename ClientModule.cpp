/*
 * ClientModule.cpp
 *
 *  Created on: 11 лип. 2014
 *      Author: maximm
 */

#include "ClientModule.h"
#include "Log.h"

ClientModule::ClientModule( Config &config, ArgumentsMap &arguments ) : Module( config, arguments )
{
}

ClientModule::~ClientModule()
{
}

void ClientModule::Init()
{
	Log::SetName( "Client" );
	Log::Add( "Init client module" );
	m_signal.Init();
	m_connection.Init();
}

void ClientModule::Run()
{
	Log::Add( "Run client module" );
	std::string ip = "127.0.0.1";
	unsigned port = 2222;

	ParseIp( m_arguments("address").m_value, ip, port );

	m_connection.Connect( ip, port );
	m_connection.Send( "ECHO: ECHO: ECHO: Test message 1 2 3" );
	Sleep( 1000 );

	m_connection.Close();
	Log::Add( "Stop client module" );
}
