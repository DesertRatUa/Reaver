/*
 * Log.cpp
 *
 *  Created on: 3 черв. 2014
 *      Author: maximm
 */

#include "Log.h"
#include <stdexcept>
#include <iostream>
#include <time.h>
#include <boost/lexical_cast.hpp>
#include <winsock2.h>

std::string Log::m_logFile("");
std::mutex Log::m_messageMut;
std::mutex Log::m_logMut;
std::ofstream Log::m_log;
std::string Log::m_name;

Log::Log()
{
}

Log::~Log()
{
	m_log.close();
}

void Log::Init( std::string path ) throw ( std::exception )
{
	m_logFile = path.substr( 0, path.find_last_of( "\\" ) ) + "\\" + "Log.log";
	m_log.open( m_logFile.c_str(), std::ios::app|std::ios::out );
	if ( m_log.fail() )
	{
		m_logFile = "";
		m_log.close();
		throw std::runtime_error( std::string("Fail open log: ") + m_logFile.c_str() );
	}
}

void Log::Close()
{
	m_log.close();
}
void Log::AddMessage( std::string message )
{
	std::lock_guard<std::mutex> lock( m_messageMut );
	std::cout << PrintTime() << "\t" << message << std::endl;
}

void Log::AddLog( std::string log )
{
	if ( !m_log.is_open() ) return;
	std::lock_guard<std::mutex> lock( m_logMut );
	m_log << PrintTime() << "\t";
	if ( !m_name.empty() )
	{
		m_log << m_name.c_str() << ": ";
	}
	m_log << log << std::endl;
}

void Log::Add( std::string log )
{
	AddMessage( log );
	AddLog( log );
}

std::string Log::PrintTime()
{
	time_t now = time(NULL);
	char buf[80];
	struct tm *tstruct;
	tstruct = localtime(&now);
	strftime(buf, sizeof(buf), "%X", tstruct);
	return buf;
}

std::string Log::IntToStr( const int value )
{
	return boost::lexical_cast<std::string>(value);
}

std::string Log::UnsignedToStr( const unsigned value )
{
	return boost::lexical_cast<std::string>(value);
}

std::string Log::AddrToStr( const sockaddr_in& addr )
{
	return std::string( inet_ntoa( addr.sin_addr ) + std::string(":") + Log::IntToStr( addr.sin_port ) );
}

void Log::SetName( const std::string &name )
{
	m_name = name;
}
