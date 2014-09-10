/*
 * RegisterMessage.cpp
 *
 *  Created on: 26 рту. 2014 у.
 *      Author: maximm
 */

#include <Messages/RegisterMessage.h>
//#include "tinyxml2.h"
#include "XMLUtils.h"

RegisterMessage::RegisterMessage() : ThreadNum(0)
{
}

RegisterMessage::RegisterMessage( const unsigned threadNum ) : ThreadNum( threadNum )
{
}

RegisterMessage::~RegisterMessage()
{
}

void RegisterMessage::_SerializeReqest( tinyxml2::XMLDocument &doc ) const
{
	XMLUtils::AddPacketId( doc, 2 );
	XMLUtils::AddUnsigned( doc, "ThreadNum", ThreadNum );
}

void RegisterMessage::_SerializeRespond( tinyxml2::XMLDocument &doc ) const
{
	XMLUtils::AddPacketId( doc, 2 );
	XMLUtils::AddText( doc, "ClientID", ClientId );
	XMLUtils::AddText( doc, "ErrorMsg", ErrorMsg );
}

void RegisterMessage::DeserializeReqest( const tinyxml2::XMLDocument &doc )
{
	XMLUtils::GetUnsigned( doc, "ThreadNum", ThreadNum );
}

void RegisterMessage::DeserializeRespond( const tinyxml2::XMLDocument &doc )
{
	XMLUtils::GetText( doc, "ClientID", ClientId );
	XMLUtils::GetText( doc, "ErrorMsg", ErrorMsg );
}
