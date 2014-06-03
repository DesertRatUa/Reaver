/*
 * Argument.cpp
 *
 *  Created on: 3 черв. 2014
 *      Author: maximm
 */

#include "Argument.h"
#include "Log.h"

Argument::Argument( const std::string &name, const std::string &shortName, const std::string &defaultValue, const std::string &description ) :
	m_name(name), m_shortName(name), m_defaultValue(defaultValue), m_description( description ), m_set(false)
{
}

Argument::~Argument()
{
}

const bool Argument::isSet()
{
	return m_set;
}

void Argument::Set()
{
	Log::Add( "Argument " + m_name + " set with default value" );
	m_set = true;
}

void Argument::Set( const std::string &value )
{
	Log::Add( "Argument " + m_name + " set with " + value + " value" );
	m_set = true;
}

void Argument::UnSet()
{
	Log::Add( "Argument " + m_name + " unset" );
	m_set = false;
}
