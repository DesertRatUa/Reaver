/*
 * ClientMessageProcessor.cpp
 *
 *  Created on: 08 рту. 2014 у.
 *      Author: maximm
 */

#include "ClientMessageProcessor.h"
#include "ClientModule.h"
#include "Log.h"

#include "Messages/RegisterMessage.h"
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
	RegisterProcessor( 2, &ClientMessageProcessor::RecieveRegisterMessage );
}

void ClientMessageProcessor::RecieveEchoMessage( const tinyxml2::XMLDocument& doc, const std::string& addr )
{
	assert( m_parent );
	EchoMessage message;
	message.DeserializeRespond( doc );
	Log::Add( "Echo message return: " + message.Text );
	m_parent->UpdateState();
	/*
	if( int pos = message.find( "ECHO" ) != -1 )
	{
		std::string rpt = message.substr( pos + 5, message.length() - pos - 5 );
		m_parent->m_connection.Send( rpt );
	}
	*/
}

void ClientMessageProcessor::RecieveRegisterMessage( const tinyxml2::XMLDocument& doc, const std::string& addr )
{
	assert( m_parent );
	RegisterMessage mess;
	mess.DeserializeRespond( doc );
	Log::Add( "Client registered with ID: " + Log::IntToStr( mess.ClientId ) );
	m_parent->UpdateState();
}

void ClientMessageProcessor::SendEchoMessage( const std::string& message )
{
	EchoMessage mess( message );
	m_parent->m_connection.Send( mess );
}

void ClientMessageProcessor::SendRegisterMessage()
{
	RegisterMessage mess;
	m_parent->m_connection.Send( mess );
}
