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
	if ( argc == 0 )
	{
		std::cout << "Failed get PATH from argc" << std::endl;
		return 0;
	}

	Config config( "argv[0]" );

	std::cout << "Running Server" << std::endl;
	getchar();
	return 0;
}


