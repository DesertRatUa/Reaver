/*
 * RegisterMessage.cpp
 *
 *  Created on: 26 ���. 2014 �.
 *      Author: maximm
 */

#include <Messages/RegisterMessage.h>

RegisterMessage::RegisterMessage() : ClientId(0)
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
	AddNum( doc, "ClientID", ClientId );
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
		ClientId = atoi( client->GetText() );
	}
	const tinyxml2::XMLElement *error = doc.FirstChildElement( "ErrorMsg" );
	if ( error )
	{
		ErrorMsg = error->GetText();
	}
}
