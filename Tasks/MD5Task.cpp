/*
 * MD5Task.cpp
 *
 *  Created on: 27 окт. 2014 г.
 *      Author: maximm
 */

#include <Tasks/MD5Task.h>
#include "Log.h"
#include "XMLUtils.h"
#include <openssl/md5.h>

MD5Task::MD5Task() : begin(0), end(0), result(0)
{
}

MD5Task::~MD5Task()
{
}

void MD5Task::SerializeRequest( tinyxml2::XMLDocument &doc ) const
{
	XMLUtils::AddInt( doc, "Begin", begin );
	XMLUtils::AddInt( doc, "End", end );
	XMLUtils::AddText( doc, "Hash", Hash );
}

void MD5Task::DeserializeRequest( const tinyxml2::XMLDocument &doc )
{
	XMLUtils::GetInt( doc, "Begin", begin );
	XMLUtils::GetInt( doc, "End", end );
	XMLUtils::GetText( doc, "Hash", Hash );
}

void MD5Task::SerializeRespond( tinyxml2::XMLDocument &doc ) const
{
	XMLUtils::AddInt( doc, "Result", result );
}

void MD5Task::DeserializeRespond( const tinyxml2::XMLDocument &doc )
{
	XMLUtils::GetInt( doc, "Result", result );
}

void MD5Task::Process()
{
	unsigned char digest[MD5_DIGEST_LENGTH];
	char mdString[33];
	std::string text;
	for ( unsigned i = begin; i < end; ++i )
	{
		text = Log::IntToStr(i);
		MD5((unsigned char*)text.c_str(), text.length(), (unsigned char*)&digest);
		for( unsigned k = 0; k < MD5_DIGEST_LENGTH; ++k )
		         sprintf(&mdString[k*2], "%02x", (unsigned int)digest[i]);
		text = mdString;
	}
}

unsigned MD5Task::GetID() const
{
	return ID;
}

void MD5Task::SetHash( const std::string &hash ) throw ( std::exception )
{
	if ( hash.length() > 32 )
	{
		throw std::runtime_error( "MD5 Hash too long" );
	}
}

std::string MD5Task::GetResult()
{
	return Log::IntToStr( result );
}
