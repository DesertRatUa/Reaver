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
