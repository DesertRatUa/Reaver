/*
 * RequestTask.cpp
 *
 *  Created on: 26 ���. 2014 �.
 *      Author: maximm
 */

#include <Messages/RequestTask.h>
#include "XMLUtils.h"

RequestTask::RequestTask( const unsigned threads ) : m_threads(threads)
{
}

RequestTask::RequestTask() : m_threads(0)
{
}

RequestTask::~RequestTask()
{
}

void RequestTask::SerializeReqest( tinyxml2::XMLDocument &doc ) const
{
	XMLUtils::AddPacketId( doc, 4 );
	XMLUtils::AddInt( doc, "Threads", m_threads );
}

void RequestTask::SerializeRespond( tinyxml2::XMLDocument &doc ) const
{
	XMLUtils::AddPacketId( doc, 4 );
}

void RequestTask::DeserializeReqest( const tinyxml2::XMLDocument &doc )
{
	XMLUtils::GetInt( doc, "Threads", m_threads );
}

void RequestTask::DeserializeRespond( const tinyxml2::XMLDocument &doc )
{

}
