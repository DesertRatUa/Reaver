/*
 * MessageProcessor.cpp
 *
 *  Created on: 06 рту. 2014 у.
 *      Author: maximm
 */

#include "MessageProcessor.h"
#include "Log.h"

MessageProcessor::MessageProcessor()
{
}

MessageProcessor::~MessageProcessor()
{
}

void MessageProcessor::ProcessMessage( const std::string& message, const std::string& addr )
{
	unsigned id = ParseMessageId( message );
	Processors::iterator prc = m_processors.find( id );
	if ( prc == m_processors.end() )
	{
		Log::Add( "No processor for message " + Log::IntToStr( id ) + ": " + message );
		return;
	}
	(*prc->second)( message, addr );
}

unsigned MessageProcessor::ParseMessageId( const std::string& message )
{
	return 1;
}

void MessageProcessor::RegisterProcessor( const unsigned id, Processor processor )
{
	m_processors[id] = processor;
}
