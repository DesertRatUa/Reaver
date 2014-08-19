/*
 * MessageProcessor.cpp
 *
 *  Created on: 06 рту. 2014 у.
 *      Author: maximm
 */

#include "MessageProcessor.h"
#include "Log.h"
#include "tinyxml2.h"

MessageProcessor::MessageProcessor()
{
}

MessageProcessor::~MessageProcessor()
{
}

void MessageProcessor::ProcessMessage( const std::string& message, const std::string& addr )
{
	tinyxml2::XMLDocument doc;
	doc.Parse( message.c_str(), message.length() );
	unsigned id = ParseMessageId( doc );
	Processors::iterator prc = m_processors.find( id );
	if ( prc == m_processors.end() )
	{
		Log::Add( "No processor for message " + Log::IntToStr( id ) + ": " + message );
		return;
	}
	(*prc->second)( doc, addr );
}

unsigned MessageProcessor::ParseMessageId( const tinyxml2::XMLDocument& doc )
{
	const tinyxml2::XMLElement *id = doc.FirstChildElement( "PacketID" );
	if ( !id )
	{
		return 0;
	}
	return atoi( id->GetText() );
}

void MessageProcessor::RegisterProcessor( const unsigned id, Processor processor )
{
	m_processors[id] = processor;
}
