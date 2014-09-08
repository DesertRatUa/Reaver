/*
 * RegisterMessage.cpp
 *
 *  Created on: 26 рту. 2014 у.
 *      Author: maximm
 */

#include <Messages/RegisterMessage.h>
#include "tinyxml2.h"

RegisterMessage::RegisterMessage()
{
}

RegisterMessage::~RegisterMessage()
{
}

void RegisterMessage::_SerializeReqest( tinyxml2::XMLDocument &doc ) const
{
	AddPacketId( doc, 2 );
}

void RegisterMessage::_SerializeRespond( tinyxml2::XMLDocument &doc ) const
{
	AddPacketId( doc, 2 );
	AddText( doc, "ClientID", ClientId );
	AddText( doc, "ErrorMsg", ErrorMsg );
}

void RegisterMessage::DeserializeReqest( const tinyxml2::XMLDocument &doc )
{

}

void RegisterMessage::DeserializeRespond( const tinyxml2::XMLDocument &doc )
{
	const tinyxml2::XMLElement *client = doc.FirstChildElement( "ClientID" );
	if ( client )
	{
		ClientId = client->GetText();
	}
	const tinyxml2::XMLElement *error = doc.FirstChildElement( "ErrorMsg" );
	if ( error )
	{
		ErrorMsg = error->GetText();
	}
}
