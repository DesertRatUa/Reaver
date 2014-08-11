/*
 * SignalHandler.cpp
 *
 *  Created on: 10 лип. 2014
 *      Author: maximm
 */

#include "SignalHandler.h"
#include "Log.h"
#include <unistd.h>

bool handled = false;

BOOL WINAPI CatchHandler( DWORD fdwCtrlType )
{
	switch( fdwCtrlType )
	{
	case CTRL_C_EVENT:
		{
		Log::Add( "CTRL + C catched" );
		handled = true;
	    return TRUE;
		}
	default : return FALSE;
	}
}

SignalHandler::SignalHandler( bool &isRun ) : m_run( isRun )
{
}

SignalHandler::~SignalHandler()
{
}

void SignalHandler::Init()
{
}

void SignalHandler::Wait()
{
	handled = false;
	if( !SetConsoleCtrlHandler( CatchHandler, TRUE ) )
	{
		Log::Add( "Signal handle failed" );
		handled = true;
	}
	while ( !handled && m_run )
	{
		usleep(100);
	}
}
