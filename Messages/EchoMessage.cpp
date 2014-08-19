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

std::string EchoMessage::Serialize() const
{
	XMLDocument doc;
	XMLPrinter printer;

	AddPacketId( doc, 1 );
	AddText( doc, "Echo", Text );

	doc.Print( &printer );
	return printer.CStr();
}

void EchoMessage::Deserialize( const tinyxml2::XMLDocument &doc )
{
	const XMLElement *text = doc.FirstChildElement( "Echo" );
	if ( text )
	{
		Text = text->GetText();
	}
}
