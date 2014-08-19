/*
 * ClientModule.cpp
 *
 *  Created on: 11 лип. 2014
 *      Author: maximm
 */

#include "ClientModule.h"
#include "Log.h"
#include "stdexcept"

ClientModule::ClientModule( Config &config, ArgumentsMap &arguments ) : Module( config, arguments ), m_connection( m_processor, m_run ), m_processor(this), m_run(false), m_signal( m_run )
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
	m_processor.Init();
}

void ClientModule::Run()
{
	Log::Add( "Run client module" );
	std::string ip = "127.0.0.1";
	unsigned port = 2222;

	ParseIp( m_arguments("address").m_value, ip, port );

	try
	{
		m_connection.Connect( ip, port );
		m_connection.Send( "ECHO: Test message" );
		m_processor.SendEchoMessage( "Echo message" );
		m_signal.Wait();
	}
	catch ( std::exception &exc )
	{
		Log::Add( "Client module exception:" + std::string( exc.what() ) );
	}

	m_connection.Close();
	Log::Add( "Stop client module" );
}
