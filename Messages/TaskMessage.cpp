/*
 * TaskMessage.cpp
 *
 *  Created on: 04 сент. 2014 г.
 *      Author: maximm
 */

#include <Messages/TaskMessage.h>

TaskMessage::TaskMessage() : SpendTime(0)
{
}

TaskMessage::TaskMessage( const unsigned spendTime ) : SpendTime( spendTime )
{

}

TaskMessage::~TaskMessage()
{
}

void TaskMessage::_SerializeReqest( tinyxml2::XMLDocument &doc ) const
{
	AddPacketId( doc, 3 );
}

void TaskMessage::_SerializeRespond( tinyxml2::XMLDocument &doc ) const
{
	AddPacketId( doc, 3 );
	AddNum( doc, "SpendTime", SpendTime );
}

void TaskMessage::DeserializeReqest( const tinyxml2::XMLDocument &doc )
{

}

void TaskMessage::DeserializeRespond( const tinyxml2::XMLDocument &doc )
{
	const tinyxml2::XMLElement *time = doc.FirstChildElement( "SpendTime" );
	if ( time )
	{
		SpendTime = atoi( time->GetText() );
	}
}
