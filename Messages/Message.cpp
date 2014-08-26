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

std::string Message::SerializeReqest() const
{
	XMLDocument doc;
	XMLPrinter printer;
	_SerializeReqest( doc );
	doc.Print( &printer );
	return printer.CStr();
}

std::string Message::SerializeRespond() const
{
	XMLDocument doc;
	XMLPrinter printer;
	_SerializeRespond( doc );
	doc.Print( &printer );
	return printer.CStr();
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

void Message::AddNum( tinyxml2::XMLDocument &doc, const std::string &name, const int num ) const
{
	AddText( doc,name, Log::IntToStr(num) );
}
