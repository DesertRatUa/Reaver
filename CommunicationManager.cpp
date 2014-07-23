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

CommunicationManager::CommunicationManager() : m_run(true), m_socket(0)
{
	m_mainThread.p = NULL;
	m_mainThread.x = 0;
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

void CommunicationManager::Close()
{
	Log::Add( "Close all connections" );

	m_run = false;
	pthread_join( m_mainThread, NULL );

	closesocket( m_socket );
	CloseAdditionalThreads();
	WSACleanup();

	Log::Add( "All connections closed" );
}

void CommunicationManager::ReadSocket( SOCKET &socket, const bool &run )
{
	char Buffer[256];
	memset( Buffer, 0, sizeof(Buffer) );

	int status = recv( socket, Buffer, sizeof(Buffer), 0 );

	while ( status != 0 && run )
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
			std::string buff(Buffer);
			Log::Add( "Recived: " + buff );

			if( int pos = buff.find( "ECHO" ) != -1 )
			{
				std::string message = buff.substr( pos + 5, buff.length() - pos - 5 );
				send( socket, message.c_str(), message.length(), 0);
			}

			memset( Buffer, 0, sizeof(Buffer) );
		}
		status = recv( socket, Buffer, sizeof(Buffer), 0 );
	}

	closesocket( socket );
}

void CommunicationManager::CloseAdditionalThreads()
{
}
