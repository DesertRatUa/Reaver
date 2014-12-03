/*
 * Message.cpp
 *
 *  Created on: 19 рту. 2014 у.
 *      Author: maximm
 */

#include <Messages/Message.h>
#include <tinyxml2.h>
using namespace tinyxml2;

Message::Message()
{
}

Message::~Message()
{
}

std::string Message::SerializeReqestStr() const
{
	XMLDocument doc;
	XMLPrinter printer;
	SerializeReqest( doc );
	doc.Print( &printer );
	return printer.CStr();
}

std::string Message::SerializeRespondStr() const
{
	XMLDocument doc;
	XMLPrinter printer;
	SerializeRespond( doc );
	doc.Print( &printer );
	return printer.CStr();
}

void Message::DeserializeReqestStr( const std::string &xml )
{
	XMLDocument doc;
	doc.Parse( xml.c_str(), xml.length() );
	DeserializeReqest( doc );
}

void Message::DeserializeRespondStr( const std::string &xml )
{
	XMLDocument doc;
	doc.Parse( xml.c_str(), xml.length() );
	DeserializeRespond( doc );
}
