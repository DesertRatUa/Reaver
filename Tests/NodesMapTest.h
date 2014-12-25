#ifndef NODESMAPTEST_H_
#define NODESMAPTEST_H_

#include <cxxtest/TestSuite.h>

#include "NodesMap.h"
#include "ServerMessageProcessor.h"

class NodesMapTest : public CxxTest::TestSuite
{
public:

	class Manager : public ServerMessageProcessorInterface
	{
	public:
		virtual void Init() {}
		virtual void SendRegisterMessage( const Client &client, const std::string *error ) {}
		virtual void SendTaskMessage( const Client &client, const TaskPtr &task ) {}
		virtual void SendCancelTaskMessage( const Client &client, const unsigned plannerId ) {};
	};
	class TestTask : public Task
	{
		virtual void _SerializeRequest( tinyxml2::XMLDocument &doc ) const {}
		virtual void _DeserializeRequest( const tinyxml2::XMLDocument &doc )  {}
		virtual void _SerializeRespond( tinyxml2::XMLDocument &doc ) const {}
		virtual void _DeserializeRespond( const tinyxml2::XMLDocument &doc ) {}
		virtual Tasks SeperateTask( const unsigned threadNums, const unsigned plannerID ) const
		{
			return Tasks();
		}
		virtual void Process() {}
		virtual unsigned GetID() const
		{
			return 0;
		}
		virtual Task* Clone()
		{
			return NULL;
		}
		virtual bool isDone()
		{
			return true;
		}
	};

	void testRegisterNode()
	{
		NodesMap map;
		Client client;
		Manager manager;
		//std::string addr( "127.0.0.1:80" );
		TS_ASSERT_THROWS_ANYTHING( map.GetNode( client ) );
		TS_ASSERT_THROWS_NOTHING( map.RegisterNode( client, 2, manager ) );
		TS_ASSERT_THROWS_NOTHING( map.GetNode( client ) );
		TS_ASSERT_THROWS_ANYTHING( map.RegisterNode( client, 2, manager ) );
	}

	void testUnregisterNode()
	{
		NodesMap map;
		Manager manager;
		//std::string addr( "127.0.0.1:80" );
		Client client;
		map.RegisterNode( client, 2, manager );
		TS_ASSERT_THROWS_NOTHING( map.UnregisterNode( client ) );
		TS_ASSERT_THROWS_ANYTHING( map.GetNode( client ) );
		TS_ASSERT_THROWS_ANYTHING( map.UnregisterNode( client ) );
	}

	void testGetNode()
	{
		NodesMap map;
		Manager manager;
		//std::string addr( "127.0.0.1:80" );
		Client client;
		TS_ASSERT_THROWS_ANYTHING( map.GetNode( client ) );
		map.RegisterNode( client, 2, manager );
		TS_ASSERT_THROWS_NOTHING( map.GetNode( client ) );
		map.UnregisterNode( client );
		TS_ASSERT_THROWS_ANYTHING( map.GetNode( client ) );
	}

	void testGetThreadsNum()
	{
		NodesMap map;
		Manager manager;
		std::string addr( "127.0.0.1:80" );
		std::string addr1( "127.0.0.1:81" );
		TaskPtr task( new TestTask() );
		Client client;
		client.addr = Log::StrToAddr( addr );
		Client client1;
		client1.addr = Log::StrToAddr( addr1 );
		map.RegisterNode( client, 2, manager );
		map.RegisterNode( client1, 3, manager );
		TS_ASSERT_EQUALS( map.GetThreadsCount(), unsigned(5) );
	}

	void testTaskComplete()
	{
//		NodesMap map;
//		Manager manager;
//		std::string addr( "127.0.0.1:80" );
//		TaskPtr task( new TestTask() );
//		map.RegisterNode( addr, 1, manager );
//		Node &node = map.GetNode( addr );
//		node.SendTask( task );
//		//TS_ASSERT( map.GetFreeNode() == NULL );
//		TS_ASSERT_THROWS_NOTHING( node.TaskComplete( task ) );
//		//TS_ASSERT( map.GetFreeNode() != NULL );
	}
};

#endif /*NODESMAPTEST_H_*/
