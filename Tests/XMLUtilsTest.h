#ifndef XMLUTILSTEST_H_
#define XMLUTILSTEST_H_

#include <cxxtest/TestSuite.h>
#include "XMLUtils.h"
#include "tinyxml2.h"

class XMLUtilsTest : public CxxTest::TestSuite
{
public:
	void testAddPacketID()
	{
		tinyxml2::XMLDocument doc;
		tinyxml2::XMLPrinter prnt;
		XMLUtils::AddPacketId( doc, 5 );
		doc.Print( &prnt );
		TS_ASSERT_EQUALS( std::string(prnt.CStr()), "<Packet PacketID=\"5\"/>\n" );
	}

	void testAddText()
	{
		tinyxml2::XMLDocument doc;
		tinyxml2::XMLPrinter prnt;
		XMLUtils::AddPacketId( doc, 5 );
		XMLUtils::AddText( doc, "Test", "Message" );
		doc.Print( &prnt );
		TS_ASSERT_EQUALS( std::string(prnt.CStr()),
				"<Packet PacketID=\"5\">\n    <Test>Message</Test>\n</Packet>\n" );
		doc.Clear();
	}

	void testAddInt()
	{
		tinyxml2::XMLDocument doc;
		tinyxml2::XMLPrinter prnt;
		XMLUtils::AddPacketId( doc, 5 );
		XMLUtils::AddInt( doc, "Test", 1 );
		doc.Print( &prnt );
		TS_ASSERT_EQUALS( std::string(prnt.CStr()), "<Packet PacketID=\"5\">\n    <Test>1</Test>\n</Packet>\n" );
	}

	void testGetText()
	{
		tinyxml2::XMLDocument doc;
		std::string xml( "<Packet PacketID=\"5\">\n    <Test>Message</Test>\n</Packet>\n" );
		doc.Parse( xml.c_str(), xml.length() );
		XMLUtils::GetText( doc, "Test", xml );
		TS_ASSERT_EQUALS( xml, "Message" );
	}

	void testGetInt()
	{
		tinyxml2::XMLDocument doc;
		std::string xml( "<Packet PacketID=\"1\">\n    <Test>1</Test>\n</Packet>\n" );
		doc.Parse( xml.c_str(), xml.length() );
		unsigned num = 0;
		XMLUtils::GetInt( doc, "Test", num );
		TS_ASSERT_EQUALS( num, unsigned(1) );
	}

	void testGetPacketId()
	{
		tinyxml2::XMLDocument doc;
		std::string xml( "<Packet PacketID=\"5\"/>\n" );
		doc.Parse( xml.c_str(), xml.length() );
		unsigned num = 0;
		XMLUtils::GetPacketId( doc, num );
		TS_ASSERT_EQUALS( num, unsigned(5) );
	}

	void testPacketId()
	{
		tinyxml2::XMLDocument doc;
		tinyxml2::XMLPrinter prnt;
		XMLUtils::AddPacketId( doc, 5 );
		doc.Print( &prnt );
		doc.Clear();
		doc.Parse( prnt.CStr(), prnt.CStrSize() );
		unsigned id = 0;
		XMLUtils::GetPacketId( doc, id );
		TS_ASSERT_EQUALS( id, unsigned(5) );
	}

};

#endif /*XMLUTILSTEST_H_*/
