/*
 * EchoMessage.cpp
 *
 *  Created on: 19 ���. 2014 �.
 *      Author: maximm
 */

#include "Messages/EchoMessage.h"
#include <XMLUtils.h>

EchoMessage::EchoMessage()
{
}

EchoMessage::EchoMessage( std::string text ) : Text(text)
{
}

EchoMessage::~EchoMessage()
{
}

void EchoMessage::SerializeReqest( tinyxml2::XMLDocument &doc ) const
{
	XMLUtils::AddPacketId( doc, 1 );
	XMLUtils::AddText( doc, "Echo", Text );
}

void EchoMessage::SerializeRespond( tinyxml2::XMLDocument &doc ) const
{
	XMLUtils::AddPacketId( doc, 1 );
	XMLUtils::AddText( doc, "Echo", Text );
}

void EchoMessage::DeserializeReqest( const tinyxml2::XMLDocument &doc )
{
	XMLUtils::GetText( doc, "Echo", Text );
}

void EchoMessage::DeserializeRespond( const tinyxml2::XMLDocument &doc )
{
	XMLUtils::GetText( doc, "Echo", Text );
}
