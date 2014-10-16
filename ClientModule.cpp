/*
 * ClientModule.cpp
 *
 *  Created on: 11 лип. 2014
 *      Author: maximm
 */

#include "ClientModule.h"
#include "Log.h"
#include "stdexcept"
#include "Tasks/Task.h"

ClientModule::ClientModule( Config &config, ArgumentsMap &arguments ) :
	Module( config, arguments ), m_connection( m_processor, m_run ), m_processor(this),
	m_run(false), m_signal( m_run ), m_respondTime(0), m_mut(0), m_state( INIT ), m_count(0),
	m_respond(false), m_sequence(0)

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
		RunSequence();
		m_signal.Wait();
	}
	catch ( std::exception &exc )
	{
		Log::Add( "Client module exception:" + std::string( exc.what() )  );
	}

	Stop();
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

	Log::Add( "Start SequenceThread" );

	while ( client->m_state < WAIT_FOR_TASK )
	{
		pthread_mutex_lock( &client->m_mut );
		switch ( client->m_state )
		{
			case INIT : client->m_state = TEST_CONNECTION;
				break;

			case TEST_CONNECTION : client->TestConnection();
				break;

			case REGISTER_CLIENT : client->RegisterClient();
				break;
		}
		pthread_mutex_unlock( &client->m_mut );
	}

	Log::Add( "End SequenceThread" );
	return NULL;
}

void ClientModule::TestConnection()
{
	m_respondTime = GetTickCount();
	m_respond = false;
	m_processor.SendEchoMessage( "TestConnection message" );
	Log::Add( "Request echo message" );
	Wait();
}

void ClientModule::ConnectionRespond()
{
	if ( m_state != TEST_CONNECTION )
	{
		Log::Add( "Wrong echo message" );
		return;
	}
	Log::Add( "Query delay: " + Log::IntToStr( GetTickCount() - m_respondTime ) + " ms" );
	Respond();
}

void ClientModule::RegisterRespond()
{
	if ( m_state != REGISTER_CLIENT )
	{
		Log::Add( "Wrong register respond" );
		return;
	}
	Respond();
}

void ClientModule::TaskRequest( TaskPtr &task )
{
	if ( m_state != WAIT_FOR_TASK )
	{
		Log::Add( "Wrong task request" );
		return;
	}
	Log::Add( "Recive Task: " + Log::IntToStr( task->GetID() ) );
	m_respondTime = GetTickCount();
	task->Process();
	Log::Add( "Task done" );
	m_processor.SendTaskMessage( GetTickCount() - m_respondTime, task );
}

void ClientModule::Stop()
{
	m_run = false;
}

void ClientModule::RegisterClient()
{
	m_respond = false;
	m_processor.SendRegisterMessage();
	Log::Add( "Request register" );
	Wait();
}

void ClientModule::Respond()
{
	//pthread_mutex_lock( &m_mut );
	m_respond = true;
	if ( m_state < WAIT_FOR_TASK  )
	{
		m_state = (State)(m_state + 1);
	}
	//pthread_mutex_unlock( &m_mut );
}

void ClientModule::Wait()
{
	m_count = 0;
	while ( !m_respond )
	{
		if ( ++m_count >= 10 )
		{
			Log::Add( "TimeOut for state: " + Log::IntToStr( m_state ) );
			m_state = FAILED;
			return;
		}
		Sleep(100);
	}
}
