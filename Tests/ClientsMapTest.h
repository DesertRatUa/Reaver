#ifndef CLIENTSMAPTEST_H_
#define CLIENTSMAPTEST_H_

#include <cxxtest/TestSuite.h>
#include "ClientsMap.h"
#include "Log.h"

class ClientsMapTest : public CxxTest::TestSuite
{
public:
	void testRegister()
	{
		ClientsMap map;
		ClientPtr client ( new Client );
		std::string addr("127.0.0.1");
		unsigned port = 8000;
		client->addr.sin_addr.s_addr = inet_addr( addr.c_str() );
		client->addr.sin_port = port;
		addr += Log::IntToStr( port );
		TS_ASSERT_EQUALS( client.use_count(), 1 );
		TS_ASSERT_THROWS_ANYTHING( map.Get( addr ) );
		TS_ASSERT_THROWS_NOTHING( map.Add( client ) );
		TS_ASSERT_THROWS_ANYTHING( map.Add( client ) );
		TS_ASSERT_EQUALS( client.use_count(), 2 );
	}

	void testUnregister()
	{
		ClientsMap map;
		ClientPtr client ( new Client );
		std::string addr("127.0.0.1");
		unsigned port = 8000;
		client->addr.sin_addr.s_addr = inet_addr( addr.c_str() );
		client->addr.sin_port = port;
		addr += Log::IntToStr( port );
		map.Add( client );
		TS_ASSERT_THROWS_NOTHING( map.Remove( client ) );
		TS_ASSERT_THROWS_ANYTHING( map.Get( addr ) );
	}

	void testRemoveDisconnected()
	{
		ClientsMap map;
		ClientPtr client ( new Client );
		ClientPtr client1 ( new Client );
		std::string addr("127.0.0.1");
		unsigned port = 8000;
		client->addr.sin_addr.s_addr = inet_addr( addr.c_str() );
		client->addr.sin_port = port;
		client1->addr.sin_addr.s_addr = inet_addr( addr.c_str() );
		client1->addr.sin_port = ++port;
		addr = "127.0.0.1:8000";
		std::string addr1 ( "127.0.0.1" );
		addr1 += Log::IntToStr( port );
		map.Add( client );
		map.Add( client1 );
		client1->Disconnect();
		map.RemoveDisconnected();
		TS_ASSERT_THROWS_ANYTHING( map.Get( addr1 ) );
		TS_ASSERT_THROWS_NOTHING( map.Get( addr ) );
	}
};

#endif /*CLIENTSMAPTEST_H_*/
