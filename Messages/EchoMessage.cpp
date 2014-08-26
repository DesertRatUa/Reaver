/*
 * EchoMessage.cpp
 *
 *  Created on: 19 рту. 2014 у.
 *      Author: maximm
 */

#include <Messages/EchoMessage.h>
#include <tinyxml2.h>
using namespace tinyxml2;

EchoMessage::EchoMessage()
{
}

EchoMessage::EchoMessage( std::string text ) : Text(text)
{
}

EchoMessage::~EchoMessage()
{
}

void EchoMessage::_SerializeReqest( tinyxml2::XMLDocument &doc ) const
{
	AddPacketId( doc, 1 );
	AddText( doc, "Echo", Text );
}

void EchoMessage::_SerializeRespond( tinyxml2::XMLDocument &doc ) const
{
	AddPacketId( doc, 1 );
	AddText( doc, "Echo", Text );
}

void EchoMessage::DeserializeReqest( const tinyxml2::XMLDocument &doc )
{
	const XMLElement *text = doc.FirstChildElement( "Echo" );
	if ( text )
	{
		Text = text->GetText();
	}
}

void EchoMessage::DeserializeRespond( const tinyxml2::XMLDocument &doc )
{
	const XMLElement *text = doc.FirstChildElement( "Echo" );
	if ( text )
	{
		Text = text->GetText();
	}
}
