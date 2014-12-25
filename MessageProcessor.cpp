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
	unsigned id = 0;
	doc.Parse( message.c_str(), message.length() );
	Packets packets( SeperatePackets( doc ) );
	for ( unsigned i = 0; i < packets.size(); ++i )
	{
		id = 0;
		tinyxml2::XMLDocument &packet = *packets.at(i);
		XMLUtils::GetPacketId( packet, id );
		if ( id == 0 )
		{
			tinyxml2::XMLPrinter printer;
			packet.Print( &printer );
			Log::Add( "Failed get PacketID from message: " + message + "\nPacket: " + std::string( printer.CStr() ) );
			return;
		}
		Processors::iterator prc = m_processors.find( id );
		if ( prc == m_processors.end() )
		{
			Log::Add( "No processor for message " + Log::IntToStr( id ) + ": " + message );
		}
		else
		{
			(*prc->second)( packet, addr );
		}
	}
}

MessageProcessor::Packets MessageProcessor::SeperatePackets( tinyxml2::XMLDocument &doc )
{
	Packets packets;
	tinyxml2::XMLElement *packet = doc.FirstChildElement( "Packet" );
	while ( packet )
	{
		packets.push_back( PacketPtr( new tinyxml2::XMLDocument() ) );
		tinyxml2::XMLDocument &ndoc = *packets.back();
		ndoc.InsertEndChild( tinyxml2::deepCopy( packet, &ndoc ) );
		doc.DeleteChild( packet );
		packet = doc.FirstChildElement( "Packet" );
	}
	/*
	if ( packets.size() > 1 )
	{
		Log::Add( "Separate message to " + Log::IntToStr( packets.size() ) + " packets" );
	}
	*/
	return packets;
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
