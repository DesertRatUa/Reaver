/*
 * Log.h
 *
 *  Created on: 3 черв. 2014
 *      Author: maximm
 */

#ifndef LOG_H_
#define LOG_H_

#include "include.h"
#include <fstream>
#include <mutex>

struct sockaddr_in;

class Log
{
public:
	Log();
	virtual ~Log();

	static void Init( std::string path ) throw ( std::exception );
	static void Close();
	static void AddMessage( std::string message );
	static void AddLog( std::string log );
	static void Add( std::string log );
	static void AddException( std::string name, const std::exception &exc );
	static std::string IntToStr( const int value );
	static std::string IntToStr( const unsigned value );
	static std::string IntToStr( const size_t &value );
	static std::string AddrToStr( const sockaddr_in& addr );
	static void SetName( const std::string &name );

protected:
	static std::string PrintTime();

	static std::string m_logFile;
	static std::mutex m_messageMut;
	static std::mutex m_logMut;

	static std::ofstream m_log;
	static std::string m_name;
};

#endif /* LOG_H_ */
