/*
 * main.cpp
 *
 *  Created on: 29 трав. 2014
 *      Author: maximm
 */
#include <iostream>
#include <stdio.h>
#include "Config.h"
#include "Log.h"
#include "ArgumentsMap.h"
#include "ServerModule.h"
#include "ClientModule.h"

int main( int argc, char *argv[] )
{
	if ( argc == 0 )
	{
		std::cout << "Failed get PATH from argc" << std::endl;
		return 0;
	}

	try
	{
		Log::Init( argv[0] );
	}
	catch ( std::exception &exc )
	{
		std::cout << "Exception: "<< exc.what() << std::endl;
	}
	Log::Add( "Server running" );

	Config config( argv[0] );
	config.Init();
	config.Read();

	ArgumentsMap arguments;
	arguments.Init();

	for( int i = 1; i < argc; ++i )
	{
		arguments.ParseArgument( argv[i] );
	}

	Module *module = NULL;

	if ( arguments("server").isSet() )
	{
		module = new ServerModule( config, arguments );
	}
	else if ( arguments("client").isSet() )
	{
		module = new ClientModule( config, arguments );
	}
	else
	{
		Log::Add( "Required one of arguments:\t\n" + arguments("server").m_description + "\t\n" + arguments("client").m_description );
	}

	if ( module )
	{
		module->Init();
		module->Run();
		delete module;
	}

	Log::Add( "Stopping Server" );
	config.Write();
	//getchar();
	return 0;
}


