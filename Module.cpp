/*
 * Module.cpp
 *
 *  Created on: 11 лип. 2014
 *      Author: maximm
 */

#include "Module.h"
#include "ServerModule.h"
#include "ClientModule.h"

Module::Module( Config &config, ArgumentsMap &arguments ) :  m_config( config ), m_arguments( arguments )
{
}

Module::~Module()
{
}

void Module::ParseIp ( const std::string &addr, std::string &ip, unsigned &port )
{
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
}

Module* Module::CreateModule( Config &config, ArgumentsMap &arguments )
{
	if ( arguments("server").isSet() && arguments("client").isSet() )
	{
		throw std::runtime_error( "Conflict of arguments:\t\n" + arguments("server").m_description + "\t\n" + arguments("client").m_description );
	}
	else if ( arguments("server").isSet() )
	{
		return new ServerModule( config, arguments );
	}
	else if ( arguments("client").isSet() )
	{
		return new ClientModule( config, arguments );
	}
	throw std::runtime_error( "Required one of arguments:\t\n" + arguments("server").m_description + "\t\n" + arguments("client").m_description );
}
