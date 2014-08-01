/*
 * Log.h
 *
 *  Created on: 3 черв. 2014
 *      Author: maximm
 */

#ifndef LOG_H_
#define LOG_H_

#include <exception>
#include <string>
#include <pthread.h>
#include <fstream>

struct sockaddr_in;

class Log
{
public:
	Log();
	virtual ~Log();

	static void Init( std::string path ) throw ( std::exception );
	static void AddMessage( std::string message );
	static void AddLog( std::string log );
	static void Add( std::string log );
	static std::string IntToStr( const int value );
	static std::string AddrToStr( const sockaddr_in& addr );

protected:
	static std::string PrintTime();

	static std::string m_logFile;
	static pthread_mutex_t m_messageMut;
	static pthread_mutex_t m_logMut;

	static std::ofstream m_log;
};

#endif /* LOG_H_ */
