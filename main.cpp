/*
 * main.cpp
 *
 *  Created on: 29 трав. 2014
 *      Author: maximm
 */
#include <iostream>
#include <stdio.h>
#include "Config.h"

int main( int argc, char *argv[] )
{
	std::cout << "Running Server" << std::endl;
	if ( argc == 0 )
	{
		std::cout << "Failed get PATH from argc" << std::endl;
		return 0;
	}

	Config config( argv[0] );
	config.Init();
	config.Read();
	config.Write();

	std::cout << "Stopping Server" << std::endl;
	//getchar();

	return 0;
}


