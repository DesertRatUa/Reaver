/*
 * MessageProcessor.cpp
 *
 *  Created on: 06 рту. 2014 у.
 *      Author: maximm
 */

#include "MessageProcessor.h"
#include "Log.h"
#include "XMLUtils.h"
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
	unsigned id = 0;
	XMLUtils::GetPacketId( doc, id );
	if ( id == 0 )
	{
		Log::Add( "Failed get PacketID from: " + message );
		return;
	}
	Processors::iterator prc = m_processors.find( id );
	if ( prc == m_processors.end() )
	{
		Log::Add( "No processor for message " + Log::IntToStr( id ) + ": " + message );
	}
	else
	{
		(*prc->second)( doc, addr );
	}
}

void MessageProcessor::RegisterProcessor( const unsigned id, Processor processor ) throw (std::runtime_error)
{
	Processors::iterator prc = m_processors.find( id );
	if ( prc != m_processors.end() )
	{
		throw std::runtime_error( "Processor for " + Log::IntToStr(id) + " already registered" );
	}
	m_processors.insert( std::pair< unsigned, Processor >( id, processor ) );
}
