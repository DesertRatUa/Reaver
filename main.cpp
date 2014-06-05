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
	config.Write();

	ArgumentsMap arguments;

	for( int i = 1; i < argc; ++i )
	{
		arguments.ParseArgument( argv[i] );
	}

	Log::Add( "Stopping Server" );
	//getchar();
	return 0;
}


