/*
 * RequestTask.cpp
 *
 *  Created on: 26 ���. 2014 �.
 *      Author: maximm
 */

#include <Messages/RequestTaskMessage.h>
#include "XMLUtils.h"

RequestTaskMessage::RequestTaskMessage( const unsigned threads ) : m_threads(threads)
{
}

RequestTaskMessage::RequestTaskMessage() : m_threads(0)
{
}

RequestTaskMessage::~RequestTaskMessage()
{
}

void RequestTaskMessage::SerializeReqest( tinyxml2::XMLDocument &doc ) const
{
	XMLUtils::AddPacketId( doc, 4 );
	XMLUtils::AddInt( doc, "Threads", m_threads );
}

void RequestTaskMessage::SerializeRespond( tinyxml2::XMLDocument &doc ) const
{
	XMLUtils::AddPacketId( doc, 4 );
}

void RequestTaskMessage::DeserializeReqest( const tinyxml2::XMLDocument &doc )
{
	XMLUtils::GetInt( doc, "Threads", m_threads );
}

void RequestTaskMessage::DeserializeRespond( const tinyxml2::XMLDocument &doc )
{

}
