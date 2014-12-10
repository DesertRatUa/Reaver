#ifndef NODETEST_H_
#define NODETEST_H_

#include <cxxtest/TestSuite.h>
#include "Node.h"
#include "ServerMessageProcessor.h"

class NodeTest : public CxxTest::TestSuite
{
public:

	class TestManager : public ServerMessageProcessorInterface
	{
		virtual void Init() {}
		virtual void SendRegisterMessage( const std::string &addr, const std::string *error ) {}
		virtual void SendTaskMessage( const std::string &addr, const TaskPtr &task ) {};
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

	void testSendTask()
	{
		std::string addr( "127.0.0.1:80" );
		TaskPtr task( new TestTask() );
		TestManager manger;
		Node node( addr, 1, manger );
		TS_ASSERT_THROWS_NOTHING( node.SendTask( task ) );
		TS_ASSERT_THROWS_ANYTHING( node.SendTask( task ) );
		TS_ASSERT_EQUALS( node.GetFreeThreadsNum(), unsigned(0) );
	}

	void testTaskComplete()
	{
		std::string addr( "127.0.0.1:80" );
		TaskPtr task( new TestTask );
		TestManager manger;
		Node node( addr, 2, manger );
		node.SendTask( task );
		node.SendTask( task );
		TS_ASSERT_THROWS_NOTHING( node.TaskComplete( task ) );
		TS_ASSERT_EQUALS( node.GetFreeThreadsNum(), unsigned(1) );
		TS_ASSERT_THROWS_NOTHING( node.TaskComplete( task ) );
		TS_ASSERT_EQUALS( node.GetFreeThreadsNum(), unsigned(2) );
		TS_ASSERT_THROWS_ANYTHING( node.TaskComplete( task ) );
	}

	void testisThreadsAvalible()
	{
		std::string addr( "127.0.0.1:80" );
		TaskPtr task( new TestTask );
		TestManager manger;
		Node node( addr, 1, manger );
		TS_ASSERT_EQUALS( node.isThreadsAvalible(), true );
		node.SendTask( task );
		TS_ASSERT_EQUALS( node.isThreadsAvalible(), false );
		node.TaskComplete( task );
		TS_ASSERT_EQUALS( node.isThreadsAvalible(), true );
	}

	void testGetFreeThreadsNum()
	{
		std::string addr( "127.0.0.1:80" );
		TaskPtr task( new TestTask );
		TestManager manger;
		Node node( addr, 2, manger );
		TS_ASSERT_EQUALS( node.GetFreeThreadsNum(), unsigned(2) );
		node.SendTask( task );
		TS_ASSERT_EQUALS( node.GetFreeThreadsNum(), unsigned(1) );
		node.SendTask( task );
		TS_ASSERT_EQUALS( node.GetFreeThreadsNum(), unsigned(0) );
	}

	void testGetID()
	{
		std::string addr( "127.0.0.1:80" );
		TestManager manger;
		Node node( addr, 1, manger );
		TS_ASSERT_EQUALS( node.GetID(), addr );
	}

	void testCheckForStaleTasks()
	{
		std::string addr( "127.0.0.1:80" );
		TaskPtr task( new TestTask() );
		TestManager manger;
		Node node( addr, 2, manger );
		node.SendTask( task );
		node.SendTask( task );
		TS_ASSERT_EQUALS( node.GetFreeThreadsNum(), (unsigned) 0 );
		node.CheckForStaleTasks( 0 );
		TS_ASSERT_EQUALS( node.GetFreeThreadsNum(), (unsigned) 2 );
	}
};

#endif /*NODETEST_H_*/
