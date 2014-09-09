/*
 * XMLUtils.h
 *
 *  Created on: 09 сент. 2014 г.
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
	static void AddUnsigned( tinyxml2::XMLDocument &doc, const std::string &name, const unsigned num );
	static void GetText( const tinyxml2::XMLDocument &doc, const std::string &name, std::string &variable );
	static void GetInt( const tinyxml2::XMLDocument &doc, const std::string &name, int &variable );
	static void GetUnsigned( const tinyxml2::XMLDocument &doc, const std::string &name, unsigned &variable );
};

#endif /* XMLUTILS_H_ */
