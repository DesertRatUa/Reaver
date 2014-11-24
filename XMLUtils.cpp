/*
 * XMLUtils.cpp
 *
 *  Created on: 09 сент. 2014 г.
 *      Author: maximm
 */

#include <XMLUtils.h>
#include "tinyxml2.h"
#include "Log.h"
#include "assert.h"
using namespace tinyxml2;

XMLUtils::XMLUtils()
{
}

XMLUtils::~XMLUtils()
{
}



void XMLUtils::AddPacketId( tinyxml2::XMLDocument &doc, const unsigned id )
{
	XMLElement* element = doc.NewElement( "Packet" );
	element->SetAttribute( "PacketID", id );
	doc.InsertFirstChild( element );
}

void XMLUtils::AddText( tinyxml2::XMLDocument &doc, const std::string &name, const std::string &text )
{
	XMLElement* parent = doc.FirstChildElement( "Packet" );
	assert(parent);
	XMLElement* element = doc.NewElement( name.c_str() );
	XMLText* txt = doc.NewText( text.c_str() );
	element->InsertEndChild( txt );
	parent->InsertEndChild( element );
}

void XMLUtils::AddInt( tinyxml2::XMLDocument &doc, const std::string &name, const int num )
{
	AddText( doc,name, Log::IntToStr(num) );
}

void XMLUtils::GetText( const tinyxml2::XMLDocument &doc, const std::string &name, std::string &variable )
{
	const XMLElement *parent = doc.FirstChildElement( "Packet" );
	assert(parent);
	const XMLElement *text = parent->FirstChildElement( name.c_str() );
	if ( text )
	{
		variable = text->GetText();
	}
}

void XMLUtils::GetInt( const tinyxml2::XMLDocument &doc, const std::string &name, unsigned &variable )
{
	std::string num;
	GetText( doc, name, num );
	if ( !num.empty() )
	{
		try
		{
			variable = atoi( num.c_str() );
		}
		catch ( ... )
		{
			Log::Add( "Failed get num from " + name );
		}
	}
}

void XMLUtils::GetPacketId( const tinyxml2::XMLDocument &doc, unsigned &variable )
{
	const XMLElement* element = doc.FirstChildElement( "Packet" );
	if ( element )
	{
		element->QueryUnsignedAttribute( "PacketID", &variable );
	}
}

void XMLUtils::AddInt( tinyxml2::XMLDocument &doc, const std::string &name, const unsigned num )
{
	AddText( doc, name, Log::IntToStr(num) );
}

void XMLUtils::AddBool( tinyxml2::XMLDocument &doc, const std::string &name, const bool value )
{
	AddText( doc, name, Log::BoolToStr( value ) );
}

void XMLUtils::GetBool( const tinyxml2::XMLDocument &doc, const std::string &name, bool &value )
{
	std::string text;
	GetText( doc, name, text );
	Log::StrToBool( text, value );
}
