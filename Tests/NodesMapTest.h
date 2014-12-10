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
		virtual void SendRegisterMessage( const std::string &addr, const std::string *error ) {}
		virtual void SendTaskMessage( const std::string &addr, const TaskPtr &task ) {}
		virtual void SendCancelTaskMessage( const std::string &addr, const unsigned plannerId ) {};
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
		Manager manager;
		std::string addr( "127.0.0.1:80" );
		TS_ASSERT_THROWS_ANYTHING( map.GetNode( addr ) );
		TS_ASSERT_THROWS_NOTHING( map.RegisterNode( addr, 2, manager ) );
		TS_ASSERT_THROWS_NOTHING( map.GetNode( addr ) );
		TS_ASSERT_THROWS_ANYTHING( map.RegisterNode( addr, 2, manager ) );
	}

	void testUnregisterNode()
	{
		NodesMap map;
		Manager manager;
		std::string addr( "127.0.0.1:80" );
		map.RegisterNode( addr, 2, manager );
		TS_ASSERT_THROWS_NOTHING( map.UnregisterNode( addr ) );
		TS_ASSERT_THROWS_ANYTHING( map.GetNode( addr ) );
		TS_ASSERT_THROWS_ANYTHING( map.UnregisterNode( addr ) );
	}

	void testGetNode()
	{
		NodesMap map;
		Manager manager;
		std::string addr( "127.0.0.1:80" );
		TS_ASSERT_THROWS_ANYTHING( map.GetNode( addr ) );
		map.RegisterNode( addr, 2, manager );
		TS_ASSERT_THROWS_NOTHING( map.GetNode( addr ) );
		map.UnregisterNode( addr );
		TS_ASSERT_THROWS_ANYTHING( map.GetNode( addr ) );
	}

	void testGetFreeNode()
	{
		NodesMap map;
		Manager manager;
		std::string addr( "127.0.0.1:80" );
		TaskPtr task( new TestTask() );
		map.RegisterNode( addr, 2, manager );
		TS_ASSERT( map.GetFreeNode() != NULL );
		Node &node = map.GetNode( addr );
		node.SendTask( task );
		TS_ASSERT( map.GetFreeNode() != NULL );
		node.SendTask( task );
		TS_ASSERT( map.GetFreeNode() == NULL );
		node.TaskComplete( task );
		TS_ASSERT( map.GetFreeNode() != NULL );
	}

	void testGetFreeThreadsNum()
	{
		NodesMap map;
		Manager manager;
		std::string addr( "127.0.0.1:80" );
		std::string addr1( "127.0.0.1:81" );
		TaskPtr task( new TestTask() );
		map.RegisterNode( addr, 2, manager );
		map.RegisterNode( addr1, 2, manager );
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
		Manager manager;
		std::string addr( "127.0.0.1:80" );
		TaskPtr task( new TestTask() );
		map.RegisterNode( addr, 1, manager );
		Node &node = map.GetNode( addr );
		node.SendTask( task );
		TS_ASSERT( map.GetFreeNode() == NULL );
		TS_ASSERT_THROWS_NOTHING( node.TaskComplete( task ) );
		TS_ASSERT( map.GetFreeNode() != NULL );
	}
};

#endif /*NODESMAPTEST_H_*/
