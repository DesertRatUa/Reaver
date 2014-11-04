#ifndef NODESMAPTEST_H_
#define NODESMAPTEST_H_

#include <cxxtest/TestSuite.h>

#include "NodesMap.h"
#include "ServerMessageProcessorInterface.h"

class NodesMapTest : public CxxTest::TestSuite, public ServerMessageProcessorInterface
{
public:

	virtual void Init() {}
	virtual void SendRegisterMessage( const std::string &addr, const std::string *error ) {}
	virtual void SendTaskMessage( const std::string &addr, TaskPtr &task ) {}

	class TestTask : public Task
	{
		virtual void SerializeRequest( tinyxml2::XMLDocument &doc ) const {}
		virtual void DeserializeRequest( const tinyxml2::XMLDocument &doc )  {}

		virtual void SerializeRespond( tinyxml2::XMLDocument &doc ) const {}
		virtual void DeserializeRespond( const tinyxml2::XMLDocument &doc ) {}

		virtual void Process() {}
		virtual unsigned GetID() const
		{
			return 0;
		}
	};

	void testRegisterNode()
	{
		NodesMap map;
		std::string addr( "127.0.0.1:80" );
		TS_ASSERT_THROWS_ANYTHING( map.GetNode( addr ) );
		TS_ASSERT_THROWS_NOTHING( map.RegisterNode( addr, 2, *this ) );
		TS_ASSERT_THROWS_NOTHING( map.GetNode( addr ) );
		TS_ASSERT_THROWS_ANYTHING( map.RegisterNode( addr, 2, *this ) );
	}

	void testUnregisterNode()
	{
		NodesMap map;
		std::string addr( "127.0.0.1:80" );
		map.RegisterNode( addr, 2, *this );
		TS_ASSERT_THROWS_NOTHING( map.UnregisterNode( addr ) );
		TS_ASSERT_THROWS_ANYTHING( map.GetNode( addr ) );
		TS_ASSERT_THROWS_ANYTHING( map.UnregisterNode( addr ) );
	}

	void testGetNode()
	{
		NodesMap map;
		std::string addr( "127.0.0.1:80" );
		TS_ASSERT_THROWS_ANYTHING( map.GetNode( addr ) );
		map.RegisterNode( addr, 2, *this );
		TS_ASSERT_THROWS_NOTHING( map.GetNode( addr ) );
		map.UnregisterNode( addr );
		TS_ASSERT_THROWS_ANYTHING( map.GetNode( addr ) );
	}

	void testGetFreeNode()
	{
		NodesMap map;
		std::string addr( "127.0.0.1:80" );
		TaskPtr task( new TestTask() );
		map.RegisterNode( addr, 2, *this );
		TS_ASSERT( map.GetFreeNode() != NULL );
		Node &node = map.GetNode( addr );
		node.SendTask( task );
		TS_ASSERT( map.GetFreeNode() != NULL );
		node.SendTask( task );
		TS_ASSERT( map.GetFreeNode() == NULL );
		node.TaskComplete();
		TS_ASSERT( map.GetFreeNode() != NULL );
	}

	void testGetFreeThreadsNum()
	{
		NodesMap map;
		std::string addr( "127.0.0.1:80" );
		std::string addr1( "127.0.0.1:81" );
		TaskPtr task( new TestTask() );
		map.RegisterNode( addr, 2, *this );
		map.RegisterNode( addr1, 2, *this );
		TS_ASSERT_EQUALS( map.GetFreeThreadsNum(), unsigned(4) );
		Node &node = map.GetNode( addr );
		node.SendTask( task );
		TS_ASSERT_EQUALS( map.GetFreeThreadsNum(), unsigned(3) );
		node.SendTask( task );
		TS_ASSERT_EQUALS( map.GetFreeThreadsNum(), unsigned(2) );
		map.GetNode(addr1).SendTask( task );
		TS_ASSERT_EQUALS( map.GetFreeThreadsNum(), unsigned(1) );
	}

	void testTaskComplete()
	{
		NodesMap map;
		std::string addr( "127.0.0.1:80" );
		TaskPtr task( new TestTask() );
		map.RegisterNode( addr, 1, *this );
		Node &node = map.GetNode( addr );
		node.SendTask( task );
		TS_ASSERT( map.GetFreeNode() == NULL );
		TS_ASSERT_THROWS_NOTHING( node.TaskComplete() );
		TS_ASSERT( map.GetFreeNode() != NULL );
	}
};

#endif /*NODESMAPTEST_H_*/
