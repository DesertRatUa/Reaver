#ifndef UNITTEST_H_
#define UNITTEST_H_

#define protected public
#define private public
#include "TestSuite.h"
#include "ClientMessageProcessor.h"
#include "tinyxml2.h"
#include "Log.h"
#include <winsock2.h>
#include "ArgumentsMap.h"
#include "Messages/EchoMessage.h"
#include "Messages/RegisterMessage.h"
#include "XMLUtils.h"
#include "NodesMap.h"

class UnitTest : public CxxTest::TestSuite
{
public:
	void TestXMLUtils(void)
	{
		using namespace tinyxml2;
		XMLDocument doc;
		XMLPrinter prnt;
		XMLUtils::AddPacketId( doc, 5 );
		doc.Print( &prnt );
		TS_ASSERT_EQUALS( prnt.CStr(), "<PacketID>5</PacketID>\n" );

		XMLUtils::AddText( doc, "Test", "Message" );
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
		XMLUtils::AddPacketId( doc, 5 );
		class Processor : public MessageProcessor
		{
			virtual void Init()
			{

			}
		};
		Processor proc;
		TS_ASSERT_EQUALS( proc.ParseMessageId(doc), 5 );
	}

	void TestEchoMessage(void)
	{
		EchoMessage mess1, mess2;
		tinyxml2::XMLDocument doc;
		mess1.Text = " TeStT ";
		std::string buff = mess1.SerializeReqest();
		doc.Parse( buff.c_str(), buff.length() );
		mess2.DeserializeReqest( doc );
		TS_ASSERT_EQUALS( mess1.Text, mess2.Text );
		mess2.Text = "Test";
		buff = mess2.SerializeRespond();
		doc.Clear();
		doc.Parse( buff.c_str(), buff.length() );
		mess1.DeserializeRespond( doc );
		TS_ASSERT_EQUALS( mess1.Text, mess2.Text );
	}

	void TestRegisterMessage(void)
	{
		RegisterMessage mess1, mess2;
		tinyxml2::XMLDocument doc;
		std::string buff = mess1.SerializeReqest();
		doc.Parse( buff.c_str(), buff.length() );
		mess2.DeserializeReqest( doc );
		buff = mess2.SerializeRespond();
		doc.Clear();
		doc.Parse( buff.c_str(), buff.length() );
		mess1.DeserializeRespond( doc );
		TS_ASSERT_EQUALS( mess1.ClientId, mess2.ClientId );
	}

	void TestNodesMap(void)
	{
		NodesMap map;
		map.RegisterNode( "1", 2 );
		TS_ASSERT_THROWS_NOTHING( map.GetNode("1") );
		map.UnregisterNode( "1" );
		TS_ASSERT_THROWS_ANYTHING( map.GetNode("1") );
		map.RegisterNode( "1", 2 );
		map.RegisterNode( "2", 2 );
		Node *free = map.GetFreeNode();
		TS_ASSERT_NO_EQUALS( free, NULL );
		TS_ASSERT_EQUALS( free->isBusy(), false );
		TS_ASSERT_EQUALS( free->isThreadsAvalible(), true );

	}
};

#endif /*UNITTEST_H_*/
