#ifndef MESSAGEPROCESSORTEST_H_
#define MESSAGEPROCESSORTEST_H_

#include <cxxtest/TestSuite.h>
#include "tinyxml2.h"
#include "XMLUtils.h"
#define protected public
#include "MessageProcessor.h"

class MessageProcessorTest : public CxxTest::TestSuite
{
public:

	static bool catched;

	class Processor : public MessageProcessor
	{
		virtual void Init()
		{

		}
	};

	static void TestProcessor( const tinyxml2::XMLDocument& doc, const std::string& addr )
	{
		catched = true;
	}

	void testRegisterProcessor()
	{
		Processor proc;
		TS_ASSERT_THROWS_NOTHING( proc.RegisterProcessor( 5, TestProcessor ) );
		TS_ASSERT_THROWS_ANYTHING( proc.RegisterProcessor( 5, TestProcessor ) );
		TS_ASSERT_THROWS_NOTHING( proc.RegisterProcessor( 6, TestProcessor ) );
	}

	void testProcessMessage()
	{
		Processor proc;
		proc.RegisterProcessor( 5, TestProcessor );
		catched = false;
		proc.ProcessMessage( "asdasdasdasdsdas", "127.0.0.1" );
		TS_ASSERT_EQUALS( catched, false );
		tinyxml2::XMLDocument doc;
		XMLUtils::AddPacketId( doc, 5 );
		tinyxml2::XMLPrinter prnt;
		doc.Print( &prnt );
		proc.ProcessMessage( prnt.CStr(), "127.0.0.1" );
		TS_ASSERT_EQUALS( catched, true );
	}
};

bool MessageProcessorTest::catched = false;

#endif /*MESSAGEPROCESSORTEST_H_*/
