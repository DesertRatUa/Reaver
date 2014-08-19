/*
 * Message.cpp
 *
 *  Created on: 19 рту. 2014 у.
 *      Author: maximm
 */

#include <Messages/Message.h>
#include <tinyxml2.h>
#include <Log.h>

using namespace tinyxml2;

Message::Message()
{
}

Message::~Message()
{
}

void Message::Deserialize( const std::string &message )
{
	tinyxml2::XMLDocument doc;
	doc.Parse( message.c_str(), message.length() );
	Deserialize( doc );
}

void Message::AddPacketId( tinyxml2::XMLDocument &doc, const unsigned id ) const
{
	AddText( doc, "PacketID", Log::IntToStr( id ) );
}

void Message::AddText( tinyxml2::XMLDocument &doc, const std::string &name, const std::string &text ) const
{
	XMLElement* element = doc.NewElement( name.c_str() );
	XMLText* txt = doc.NewText( text.c_str() );
	element->InsertEndChild( txt );
	doc.InsertEndChild( element );
}
