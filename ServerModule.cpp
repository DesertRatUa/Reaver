/*
 * ServerModule.cpp
 *
 *  Created on: 13 черв. 2014
 *      Author: maximm
 */

#include "ServerModule.h"
#include "Log.h"


ServerModule::ServerModule( Config &config, ArgumentsMap &arguments ) : m_config( config ), m_arguments( arguments )
{
}

ServerModule::~ServerModule()
{
}

void ServerModule::Init()
{
	Log::Add( "Init server module" );
}

void ServerModule::Run()
{
	Log::Add( "Run server module" );
	const std::string& addr = m_arguments("address").m_value;
	unsigned port = 2222;
	std::string ip = "*";
	int pos = addr.find( ":" );

	if( pos != -1 )
	{
		port = atoi( addr.substr( pos, addr.length() - pos ).c_str() );
		ip = addr.substr( 0, pos );
	}
	else
	{
		ip = addr;
	}

	m_connection.Listen( ip, port );

	Sleep( 100 );

	m_connection.Close();
	Log::Add( "Stop server module" );
}
