/*
 * XMLUtils.cpp
 *
 *  Created on: 09 сент. 2014 г.
 *      Author: maximm
 */

#include <XMLUtils.h>
#include "tinyxml2.h"
#include "Log.h"
using namespace tinyxml2;

XMLUtils::XMLUtils()
{
}

XMLUtils::~XMLUtils()
{
}

void XMLUtils::AddPacketId( tinyxml2::XMLDocument &doc, const unsigned id )
{
	AddText( doc, "PacketID", Log::IntToStr( id ) );
}

void XMLUtils::AddText( tinyxml2::XMLDocument &doc, const std::string &name, const std::string &text )
{
	XMLElement* element = doc.NewElement( name.c_str() );
	XMLText* txt = doc.NewText( text.c_str() );
	element->InsertEndChild( txt );
	doc.InsertEndChild( element );
}

void XMLUtils::AddInt( tinyxml2::XMLDocument &doc, const std::string &name, const int num )
{
	AddText( doc,name, Log::IntToStr(num) );
}

void XMLUtils::GetText( const tinyxml2::XMLDocument &doc, const std::string &name, std::string &variable )
{
	const XMLElement *text = doc.FirstChildElement( name.c_str() );
	if ( text )
	{
		variable = text->GetText();
	}
}

void XMLUtils::GetUnsigned( const tinyxml2::XMLDocument &doc, const std::string &name, unsigned &variable )
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

void XMLUtils::AddUnsigned( tinyxml2::XMLDocument &doc, const std::string &name, const unsigned num )
{
	AddText( doc,name, Log::UnsignedToStr(num) );
}
