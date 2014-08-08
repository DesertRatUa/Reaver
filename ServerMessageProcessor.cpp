/*
 * ServerMessageProcessor.cpp
 *
 *  Created on: 08 рту. 2014 у.
 *      Author: maximm
 */

#include "ServerMessageProcessor.h"
#include "ServerModule.h"
#include "Log.h"

ServerModule *ServerMessageProcessor::m_parent(NULL);

ServerMessageProcessor::ServerMessageProcessor( ServerModule *parent )
{
	m_parent = parent;
}

ServerMessageProcessor::~ServerMessageProcessor()
{
}

void ServerMessageProcessor::Init()
{
	RegisterProcessor( 1, &ServerMessageProcessor::RecieveEchoMessage );
}

void ServerMessageProcessor::RecieveEchoMessage( const std::string& message, const std::string& addr )
{
	if ( !m_parent )
	{
		return;
	}

	Log::Add( "Recived: " + message );

	if( int pos = message.find( "ECHO" ) != -1 )
	{
		std::string rpt = message.substr( pos + 5, message.length() - pos - 5 );
		m_parent->m_connection.GetClient( addr ).Send( rpt );
	}
}
