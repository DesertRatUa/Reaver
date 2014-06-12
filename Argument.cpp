/*
 * Argument.cpp
 *
 *  Created on: 3 черв. 2014
 *      Author: maximm
 */

#include "Argument.h"
#include "Log.h"

Argument::Argument( const std::string &name, const std::string &shortName, const std::string &defaultValue, const std::string &description ) :
	m_name(name), m_shortName(shortName), m_value(defaultValue), m_description( description ), m_set(false)
{
}

Argument::~Argument()
{
}

bool Argument::isSet() const
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
	m_value = value;
}

void Argument::UnSet()
{
	Log::Add( "Argument " + m_name + " unset" );
	m_set = false;
}

bool Argument::operator== ( const Argument& arg ) const
{
	return arg.m_name == m_name || arg.m_shortName == m_shortName;
}
