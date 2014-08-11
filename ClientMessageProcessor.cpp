/*
 * ClientMessageProcessor.cpp
 *
 *  Created on: 08 рту. 2014 у.
 *      Author: maximm
 */

#include "ClientMessageProcessor.h"
#include "ClientModule.h"
#include "Log.h"
#include "tinyxml2.h"

using namespace tinyxml2;

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

void ClientMessageProcessor::RecieveEchoMessage( const std::string& message, const std::string& addr )
{
	if ( !m_parent )
	{
		return;
	}

	Log::Add( "Recived: " + message );

	if( int pos = message.find( "ECHO" ) != -1 )
	{
		std::string rpt = message.substr( pos + 5, message.length() - pos - 5 );
		m_parent->m_connection.Send( rpt );
	}
}

void ClientMessageProcessor::SendEchomMessage( const std::string& message )
{
	XMLDocument doc;
	XMLPrinter printer;

	XMLElement* element = doc.NewElement( "PacketID" );
	XMLText* text = doc.NewText("1");
	element->InsertEndChild( text );
	doc.InsertEndChild( element );

	element = doc.NewElement( "Echo" );
	text = doc.NewText( message.c_str() );
	element->InsertEndChild( text );
	doc.InsertEndChild( element );

	doc.Print( &printer );
	m_parent->m_connection.Send( printer.CStr() );
}
