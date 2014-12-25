/*
 * CommunicationManager.cpp
 *
 *  Created on: 13 черв. 2014
 *      Author: maximm
 */

#include "CommunicationManager.h"
#include "Log.h"
#include <stdio.h>
#include <sys/types.h>
#include <algorithm>
#include <stdexcept>
#include "MessageProcessor.h"
#include <thread>

CommunicationManager::CommunicationManager( MessageProcessor &processor, bool &isRun ) :
	m_socket(0), m_processor( processor ), m_run( isRun )
{
}

CommunicationManager::~CommunicationManager()
{
}

void CommunicationManager::Init()
{
	m_timeout.tv_sec = 1;  // Zero timeout (poll)
	m_timeout.tv_usec = 0;
	memset( &m_address, 0, sizeof(m_address) );

	if ( WSAStartup(0x202, &m_wsaData) != 0 )
	{
		std::string error("Failed to init data");
		Log::Add( error );
		throw( std::runtime_error(error) );
	}

	m_socket = socket( AF_INET, SOCK_STREAM, 0 );
	if ( m_socket == INVALID_SOCKET)
	{
		std::string error( "Failed to open socket: " + WSAGetLastError() );
		Log::Add( error );
		throw( std::runtime_error(error) );
	}
}

void CommunicationManager::Stop()
{
	Log::Add( "Close all connections" );

	if ( m_mainThread.get() )
	{
		m_mainThread->join();
	}

	closesocket( m_socket );
	CloseAdditionalThreads();
	WSACleanup();

	Log::Add( "All connections closed" );
}

void CommunicationManager::ReadSocket( SOCKET &socket, CommunicationManager& manager, const std::string &add )
{
	char Buffer[4048];
	memset( Buffer, 0, sizeof(Buffer) );

	int status = recv( socket, Buffer, sizeof(Buffer), 0 );

	while ( status != 0 && manager.m_run )
	{
		if( status == SOCKET_ERROR )
		{
			if ( WSAGetLastError() == 10035 )
			{
				Sleep(100);
			}
			else
			{
				Log::Add( "Failed get data from scoket: " + Log::IntToStr( WSAGetLastError() ) );
				break;
			}
		}
		else
		{
			manager.m_processor.ProcessMessage( Buffer, add );
		}
		memset( Buffer, 0, sizeof(Buffer) );
		status = recv( socket, Buffer, sizeof(Buffer), 0 );
	}

	closesocket( socket );
}

void CommunicationManager::CloseAdditionalThreads()
{
}
