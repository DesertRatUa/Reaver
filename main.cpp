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
		std::cout << "Log init exception: "<< exc.what() << std::endl;
	}
	Log::Add( "Server running" );

	Config config( argv[0] );
	config.Init();
	config.Read();

	ArgumentsMap arguments;
	arguments.Init();
	arguments.ParseArguments( argc, argv );

	Module *module = NULL;
	try
	{
		module = Module::CreateModule( config, arguments );
		module->Init();
		module->Run();
	}
	catch ( std::exception &exc )
	{
		Log::AddException( "Module", exc );
	}
	delete module;

	Log::Add( "Stopping Server" );
	config.Write();
	//getchar();
	return 0;
}


