#ifndef UNITTEST_H_
#define UNITTEST_H_

#define protected public
#define private public
#include <cxxtest/TestSuite.h>
#include "ClientMessageProcessor.h"
#include "tinyxml2.h"
#include "Log.h"
#include <winsock2.h>
#include "ArgumentsMap.h"
#include "Messages/EchoMessage.h"

class UnitTest : public CxxTest::TestSuite
{
public:
	void TestClientMessageProcessor(void)
	{
		using namespace tinyxml2;
		XMLDocument doc;
		XMLPrinter prnt;
		EchoMessage mess;
		mess.AddPacketId( doc, 5 );
		doc.Print( &prnt );
		TS_ASSERT_EQUALS( prnt.CStr(), "<PacketID>5</PacketID>\n" );

		mess.AddText( doc, "Test", "Message" );
		prnt.ClearBuffer();
		doc.Print( &prnt );
		TS_ASSERT_EQUALS( prnt.CStr(), "\n<PacketID>5</PacketID>\n\n<Test>Message</Test>\n" ); // WTF????
	}

	void TestLog(void)
	{
		TS_ASSERT_EQUALS( Log::IntToStr( 123 ).c_str(), "123" );
		sockaddr_in addr;
		addr.sin_addr.s_addr = inet_addr( "127.0.0.1" );
		addr.sin_port = 89;
		TS_ASSERT_EQUALS( Log::AddrToStr( addr ).c_str(), "127.0.0.1:89" );

		TS_ASSERT_THROWS_ANYTHING( Log::Init( "C:\\Tmp_NoExist\\" ) );
		TS_ASSERT_THROWS_NOTHING( Log::Init( "C:\\Windows\\Temp\\" ) );
		std::fstream file( "C:\\Windows\\Temp\\Log.log", std::ios::in );
		TS_ASSERT_EQUALS( file.is_open(), true );
		file.close();
		Log::Close();
	}

	void TestArgumentMap(void)
	{
		ArgumentsMap map;
		map.AddArgument( "FirstArg", "frst", "SET!", "First agrument descr" );
		TS_ASSERT_THROWS_NOTHING( map.Get("FirstArg") );
		TS_ASSERT_THROWS_ANYTHING( map.Get("FirstArg1") );
		TS_ASSERT_THROWS_NOTHING( map.GetShort("frst") );
		TS_ASSERT_THROWS_ANYTHING( map.GetShort("frst1") );
		TS_ASSERT_EQUALS( map.Get("FirstArg").isSet(), false );
		map.Get("FirstArg").Set();
		TS_ASSERT_EQUALS( map.Get("FirstArg").isSet(), true );
		TS_ASSERT_EQUALS( map.Get("FirstArg").m_value, "SET!" );
	}
	void TestPacketId(void)
	{
		using namespace tinyxml2;
		XMLDocument doc;
		EchoMessage mess;
		mess.AddPacketId( doc, 5 );
		class Processor : public MessageProcessor
		{
			virtual void Init()
			{

			}
		};
		Processor proc;
		TS_ASSERT_EQUALS( proc.ParseMessageId(doc), 5 );
	}
};

#endif /*UNITTEST_H_*/
