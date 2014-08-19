/*
 * ClientMessageProcessor.cpp
 *
 *  Created on: 08 рту. 2014 у.
 *      Author: maximm
 */

#include "ClientMessageProcessor.h"
#include "ClientModule.h"
#include "Log.h"

#include "Messages/EchoMessage.h"

ClientModule *ClientMessageProcessor::m_parent(NULL);

ClientMessageProcessor::ClientMessageProcessor( ClientModule *parent  )
{
	m_parent = parent;
}

ClientMessageProcessor::~ClientMessageProcessor()
{
}

void ClientMessageProcessor::Init()
{
	RegisterProcessor( 1, &ClientMessageProcessor::RecieveEchoMessage );
}

void ClientMessageProcessor::RecieveEchoMessage( const tinyxml2::XMLDocument& doc, const std::string& addr )
{
	assert( m_parent );
	EchoMessage message;
	message.Deserialize( doc );
	Log::Add( "Echo message return: " + message.Text );
	/*
	if( int pos = message.find( "ECHO" ) != -1 )
	{
		std::string rpt = message.substr( pos + 5, message.length() - pos - 5 );
		m_parent->m_connection.Send( rpt );
	}
	*/
}

void ClientMessageProcessor::SendEchoMessage( const std::string& message )
{
	EchoMessage mess( message );
	m_parent->m_connection.Send( mess );
}
