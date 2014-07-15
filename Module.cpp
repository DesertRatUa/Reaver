/*
 * Module.cpp
 *
 *  Created on: 11 лип. 2014
 *      Author: maximm
 */

#include "Module.h"

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
