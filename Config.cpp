/*
 * Config.cpp
 *
 *  Created on: 29 ����. 2014
 *      Author: maximm
 */

#include "Config.h"
#include <unistd.h>
#include <errno.h>
#include <boost/property_tree/ini_parser.hpp>
#include <iostream>

Config::Config( std::string path ) :NodeType( UNDEFINED ), ServerIp("127.0.0.1"), ServerPort(1025), m_path(path)
{
	m_configFile = m_path.substr( 0, m_path.find_last_of( "\\" ) ) + "\\" + "Config.cfg";
}

Config::~Config()
{
}

void Config::Init()
{
}

void Config::Read()
{
	std::cout << "Config file location:" << m_configFile << std::endl;

	if ( !access( m_configFile.c_str() , R_OK ) )
	{
		boost::property_tree::ini_parser::read_ini( m_configFile , m_configTree );

		unsigned isServer = 0;
		GetValue<unsigned>( "Server", isServer );
		NodeType = isServer > 0 ? SERVER : CLIENT;

		if ( NodeType == CLIENT )
		{
			GetValue<std::string>( "Server_IP", ServerIp );
			GetValue<unsigned>( "Server_Port", ServerPort );
		}
	}
	else
	{
		std::cout << "No config file " << m_configFile << std::endl;
	}
}

void Config::Write()
{
	m_configTree.clear();
	m_configTree.add( "Server", unsigned(NodeType) - 1 );
	m_configTree.add( "Server_IP", ServerIp );
	m_configTree.add( "Server_Port", ServerPort );
	boost::property_tree::write_ini( m_configFile, m_configTree );
}

template< typename T >
void Config::GetValue( std::string ValueName, T& ValueStorage )
{
	try
	{
		ValueStorage = m_configTree.get<T>( ValueName );
	}
	catch( std::exception &exc )
	{
	}
}
