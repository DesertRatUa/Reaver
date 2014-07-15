/*
 * ArgumentsMap.cpp
 *
 *  Created on: 3 черв. 2014
 *      Author: maximm
 */

#include "ArgumentsMap.h"
#include <algorithm>
#include <stdexcept>
#include "Log.h"

ArgumentsMap::ArgumentsMap()
{
}

ArgumentsMap::~ArgumentsMap()
{
}

void ArgumentsMap::Init()
{
	AddArgument( "server", "s", "", "Start server" );
	AddArgument( "client", "c", "", "Start client" );
	AddArgument( "address", "a", "127.0.0.1", "Listen/connect addr" );
}

void ArgumentsMap::Set( const std::string &name ) throw ( std::exception )
{
	Get(name).Set();
}

void ArgumentsMap::Set( const std::string &name, const std::string &value )
{
	Get(name).Set(value);
}

void ArgumentsMap::ParseArgument( std::string name )
{
	int delimeter = name.find( "-" );

	if ( delimeter < 0 )
	{
		Log::Add( "Argument parse failed: " + name );
		return;
	}

	Log::AddMessage( "Argument: " + name );
	name = name.substr( delimeter + 1, name.length() - delimeter - 1 );

	Argument tmpArg("tmp","t","","");

	delimeter = name.find( "=" );
	if ( delimeter == -1 )
	{
		tmpArg.m_set = true;
	}
	else
	{
		tmpArg.Set( name.substr( delimeter + 1, name.length() - delimeter -1 ) );
		name = name.substr( 0 , delimeter );
	}

	delimeter = name.find( "-" );

	if ( delimeter == -1 )
	{
		Log::AddMessage( "Short name: " + name );
		tmpArg.m_shortName = name;
	}
	else
	{
		name = name.substr( delimeter + 1, name.length() - delimeter -1 );
		Log::AddMessage( "Name: " + name );
		tmpArg.m_name = name;
	}
	try
	{
		Argument& arg = Get( tmpArg );
		if ( tmpArg.m_value == "" )
		{
			arg.Set();
		}
		else
		{
			arg.Set( tmpArg.m_value );
		}
	}
	catch ( std::exception &exc )
	{
		Log::Add( "Argument parse failed: " + name + ". Exception: " + exc.what() );
	}
}

void ArgumentsMap::UnSet( const std::string &name ) throw ( std::exception )
{
	Get(name).UnSet();
}

Argument& ArgumentsMap::Get( const std::string &name ) throw ( std::exception )
{
	for ( Arguments::iterator argument = m_arguments.begin(); argument != m_arguments.end(); ++argument )
	{
		if ( argument->m_name == name ) return *argument;
	}
	throw std::runtime_error("Unregistered argument");
}

Argument& ArgumentsMap::GetShort( const std::string &name ) throw ( std::exception )
{
	for ( Arguments::iterator argument = m_arguments.begin(); argument != m_arguments.end(); ++argument )
	{
		if ( argument->m_shortName == name ) return *argument;
	}
	throw std::runtime_error("Unregistered argument");
}

Argument& ArgumentsMap::operator()( const std::string &name )
{
	return Get( name );
}

Argument& ArgumentsMap::Get( const Argument &arg ) throw ( std::exception )
{
	Arguments::iterator argument = std::find( m_arguments.begin(), m_arguments.end(), arg );

	if( argument == m_arguments.end() )
	{
		throw std::runtime_error("Unregistered argument");
	}

	return *argument;
}

void ArgumentsMap::AddArgument( std::string Name, std::string ShortName, std::string DefaultValue, std::string Description )
{
	m_arguments.push_back( Argument( Name, ShortName,  DefaultValue, Description ) );
}
