/*
 * ArgumentsMap.cpp
 *
 *  Created on: 3 черв. 2014
 *      Author: maximm
 */

#include "ArgumentsMap.h"
#include <algorithm>
#include <stdexcept>

ArgumentsMap::ArgumentsMap()
{
}

ArgumentsMap::~ArgumentsMap()
{
}

void ArgumentsMap::Init()
{
}

void ArgumentsMap::Set( const std::string &name )
{

}

void ArgumentsMap::Set( const std::string &name, const std::string &value )
{

}

void ArgumentsMap::UnSet( const std::string &name )
{

}

Argument& ArgumentsMap::Get( const std::string &name ) throw ( std::exception )
{
	ArgumentMap::iterator arg = m_arguments.find(name );

	if ( arg == m_arguments.end() )
	{
		throw std::runtime_error("Unregistered argument");
	}

	return arg->second;
}

void ArgumentsMap::AddArgument( std::string Name, std::string ShortName, std::string DefaultValue, std::string Description )
{
	m_arguments.insert( ArgumentPair( Name, Argument( Name, ShortName,  DefaultValue, Description ) ) );
}
