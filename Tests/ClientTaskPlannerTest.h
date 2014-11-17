#ifndef CLIENTTASKPLANNERTEST_H_
#define CLIENTTASKPLANNERTEST_H_

#include <cxxtest/TestSuite.h>
#define protected public
#include "ClientTaskPlanner.h"
#include "ClientMessageProcessor.h"
#undef protected
#include <winsock2.h>
#include <windows.h>
#include "Log.h"

class ClientTaskPlannerTest : public CxxTest::TestSuite
{
public:

	class TestTask : public Task
	{
	public:
		~TestTask()
		{
			Log::Add( "Destroy" );
		}

		unsigned count = 0;
		std::mutex mut;

		virtual void SerializeRequest( tinyxml2::XMLDocument &doc ) const {}
		virtual void DeserializeRequest( const tinyxml2::XMLDocument &doc )  {}
		virtual void SerializeRespond( tinyxml2::XMLDocument &doc ) const {}
		virtual void DeserializeRespond( const tinyxml2::XMLDocument &doc ) {}
		virtual Tasks SeperateTask( const unsigned threadNums, const unsigned plannerID ) const
		{
			Tasks tasks;
			return tasks;
		}
		virtual void Process()
		{
			std::lock_guard<std::mutex> lock(mut);
			++count;
		}
		virtual unsigned GetID() const
		{
			return 0;
		}
	};

	class TestProc : public ClientMessageProcessorInterface
	{
	public:
		virtual void SendEchoMessage( const std::string& messag ) {}
		virtual void SendRegisterMessage() {};
		virtual	void SendTaskMessage( const unsigned long time, TaskPtr &task ) {};
	};

	void testAddTask()
	{
		TestProc proc;
		ClientTaskPlanner planner( proc, 2 );
		TaskPtr task( new TestTask() );
		TS_ASSERT_EQUALS( planner.m_tasks.size(), unsigned(0) );
		planner.AddTask( task );
		TS_ASSERT_EQUALS( planner.m_tasks.size(), unsigned(1) );
		planner.AddTask( task );
		TS_ASSERT_EQUALS( planner.m_tasks.size(), unsigned(2) );
	}

	void testRun()
	{
		TestProc proc;
		ClientTaskPlanner planner( proc, 2 );
		TaskPtr task( new TestTask() );
		TestTask &tt = dynamic_cast<TestTask&>(*task.get());
		TS_ASSERT_EQUALS( tt.count, unsigned(0) );
		planner.AddTask( task );
		planner.AddTask( task );
		planner.AddTask( task );
		planner.AddTask( task );
		planner.Run();
		Sleep(30000);
		planner.Stop();
		TS_ASSERT_EQUALS( tt.count, unsigned(4) );
	}

};

#endif /*CLIENTTASKPLANNERTEST_H_*/
