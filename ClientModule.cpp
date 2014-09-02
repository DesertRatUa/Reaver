/*
 * ClientModule.cpp
 *
 *  Created on: 11 лип. 2014
 *      Author: maximm
 */

#include "ClientModule.h"
#include "Log.h"
#include "stdexcept"

ClientModule::ClientModule( Config &config, ArgumentsMap &arguments ) : Module( config, arguments ), m_connection( m_processor, m_run ), m_processor(this), m_run(false), m_signal( m_run ), m_respondTime(0), m_mut(0), m_state( INIT ), m_lastState( INIT ), m_count(0)
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
	pthread_mutex_init( &m_mut, NULL );
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
		TestConnection();
		m_signal.Wait();
	}
	catch ( std::exception &exc )
	{
		Log::Add( "Client module exception:" + std::string( exc.what() )  );
	}

	m_connection.Close();
	Log::Add( "Stop client module" );
}

void ClientModule::RunSequence()
{
	pthread_create( &m_sequence, NULL, ClientModule::SequenceThread, (void* ) this );
}

void* ClientModule::SequenceThread( void *arg )
{
	assert( arg );

	ClientModule *client = (ClientModule*) arg;

	assert( client->m_state == INIT );
	assert( client->m_lastState == INIT );

	while ( client->m_run )
	{
		pthread_mutex_lock( &m_mut );
		switch ( client->m_state )
		{
			case INIT : client->m_state = TEST_CONNECTION;
				break;

			case TEST_CONNECTION : client->TestConnection();
				break;

			case REGISTER_CLIENT : client->RegisterClient();
				break;

			case FAILED:
			case DONE:
				client->Stop();
		}
		Sleep(1);
		pthread_mutex_unlock( &m_mut );
	}
	return NULL;
}

void ClientModule::TestConnection()
{
	if ( m_lastState != INIT )
	{
		if ( ++m_count >= 10 )
		{
			Log::Add( "TimeOut for test connection" );
			m_state = FAILED;
		}
	}
	else
	{
		m_respondTime = GetTickCount();
		m_processor.SendEchoMessage( "TestConnection message" );
		m_lastState = TEST_CONNECTION;
	}
}

void ClientModule::ConnectionRespond()
{
	Log::Add( "Query delay: " + Log::IntToStr( GetTickCount() - m_respondTime ) + " ms" );
	Respond();
}

void ClientModule::RegisterRespond()
{
	Stop();
}

void ClientModule::Stop()
{
	m_run = false;
}

unsigned ClientModule::GetLastTick()
{
	return m_respondTime;
}

void ClientModule::RegisterClient()
{
	if ( m_lastState != INIT )
	{
		if ( ++m_count >= 10 )
		{
			Log::Add( "TimeOut for Register Client" );
			m_state = FAILED;
		}
	}
	else
	{
		m_processor.SendRegisterMessage();
		Log::Add( "Request register" );
	}
}

void ClientModule::Respond()
{
	pthread_mutex_lock( &m_mut );
	if ( m_state < DONE )
	{
		m_state = (State)(m_state + 1);
	}
	pthread_mutex_unlock( &m_mut );
}
