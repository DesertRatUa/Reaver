/*
 * SignalHandler.cpp
 *
 *  Created on: 10 лип. 2014
 *      Author: maximm
 */

#include "SignalHandler.h"
#include "Log.h"
#include <unistd.h>

SignalHandler::SignalHandler() : m_run(NULL), m_handled(false)
{
}

SignalHandler::~SignalHandler()
{
}

void SignalHandler::Init()
{
	pthread_mutex_init( &m_run, NULL );
}

void SignalHandler::Wait()
{
	//pthread_mutex_lock( &m_run );
	pthread_create( &m_mainThread, NULL, &Thread, (void*)this );
	//pthread_mutex_lock( &m_run );
	//pthread_mutex_unlock( &m_run );
	pthread_join( m_mainThread, NULL );
}

BOOL SignalHandler::CatchHandler( DWORD fdwCtrlType )
{
	switch( fdwCtrlType )
	{
	case CTRL_C_EVENT:
		{
		Log::Add( "CTRL + C catched" );
		m_handled = true;
	    return TRUE;
		}
	default : return FALSE;
	}
}

void *SignalHandler::Thread( void *parent )
{
	Log::Add( "Signal thread start" );
	SignalHandler *handler = ( SignalHandler* ) parent;
	handler->m_handled = false;
	if( !SetConsoleCtrlHandler( (PHANDLER_ROUTINE) &SignalHandler::CatchHandler, TRUE ) )
	{
		Log::Add( "Signal handle failed" );
	}
	while ( !handler->m_handled )
	{
		usleep(100);
	}
	Log::Add( "Signal thread stop" );
	pthread_exit(NULL);
	//pthread_mutex_unlock( &m_run );
	return NULL;
}
