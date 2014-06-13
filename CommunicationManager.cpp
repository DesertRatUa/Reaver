/*
 * CommunicationManager.cpp
 *
 *  Created on: 13 черв. 2014
 *      Author: maximm
 */

#include "CommunicationManager.h"
#include "Log.h"
#include <boost/lexical_cast.hpp>

CommunicationManager::CommunicationManager()
{
}

CommunicationManager::~CommunicationManager()
{
}

void CommunicationManager::Connect( const std::string &addr, const unsigned port )
{

}

void CommunicationManager::Listen( const std::string &addr, const unsigned port )
{
	Log::Add( "Start listen on " + addr + ":" + boost::lexical_cast<std::string>(port) );
}


void CommunicationManager::Close()
{
	Log::Add( "Close all connections" );
}
