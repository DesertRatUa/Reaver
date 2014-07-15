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

std::string Log::m_logFile("");
pthread_mutex_t Log::m_messageMut(NULL);
pthread_mutex_t Log::m_logMut(NULL);
std::ofstream Log::m_log;

Log::Log()
{
}

Log::~Log()
{
	m_log.close();
}

void Log::Init( std::string path ) throw ( std::exception )
{
	pthread_mutex_init( &m_messageMut, NULL );
	pthread_mutex_init( &m_logMut, NULL );

	m_logFile = path.substr( 0, path.find_last_of( "\\" ) ) + "\\" + "Log.log";
	m_log.open( m_logFile.c_str(), std::ios::app|std::ios::out );
	if ( m_log.fail() )
	{
		m_logFile = "";
		m_log.close();
		throw std::runtime_error( std::string("Fail open log: ") + m_logFile.c_str() );
	}
}

void Log::AddMessage( std::string message )
{
	pthread_mutex_lock( &m_messageMut );
	std::cout << PrintTime() << "\t" << message << std::endl;
	pthread_mutex_unlock( &m_messageMut );
}

void Log::AddLog( std::string log )
{
	if ( !m_log.is_open() ) return;
	pthread_mutex_lock( &m_logMut );
	m_log << PrintTime() << "\t" << log << std::endl;
	pthread_mutex_unlock( &m_logMut );
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
