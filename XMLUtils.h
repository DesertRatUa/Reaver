/*
 * XMLUtils.h
 *
 *  Created on: 09 ����. 2014 �.
 *      Author: maximm
 */

#ifndef XMLUTILS_H_
#define XMLUTILS_H_

#include "include.h"

class XMLUtils
{
public:
	XMLUtils();
	virtual ~XMLUtils();

	static void AddPacketId( tinyxml2::XMLDocument &doc, const unsigned id );
	static void AddText( tinyxml2::XMLDocument &doc, const std::string &name, const std::string &text );
	static void AddInt( tinyxml2::XMLDocument &doc, const std::string &name, const int num );
	static void AddInt( tinyxml2::XMLDocument &doc, const std::string &name, const unsigned num );
	static void GetText( const tinyxml2::XMLDocument &doc, const std::string &name, std::string &variable );
	static void GetInt( const tinyxml2::XMLDocument &doc, const std::string &name, int &variable );
	static void GetInt( const tinyxml2::XMLDocument &doc, const std::string &name, unsigned &variable );
	static void GetPacketId( const tinyxml2::XMLDocument &doc, unsigned &variable );
	static void AddBool( tinyxml2::XMLDocument &doc, const std::string &name, const bool value );
	static void GetBool( const tinyxml2::XMLDocument &doc, const std::string &name, bool &value );

	static std::string XMLtoStr( const tinyxml2::XMLDocument &doc );
};

#endif /* XMLUTILS_H_ */
