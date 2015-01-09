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

		virtual void _SerializeRequest( tinyxml2::XMLDocument &doc ) const {}
		virtual void _DeserializeRequest( const tinyxml2::XMLDocument &doc )  {}
		virtual void _SerializeRespond( tinyxml2::XMLDocument &doc ) const {}
		virtual void _DeserializeRespond( const tinyxml2::XMLDocument &doc ) {}
		virtual Tasks SeperateTask( const unsigned threadNums, const unsigned plannerID ) const
		{
			Tasks tasks;
			return tasks;
		}
		virtual void Process()
		{
			//std::lock_guard<std::mutex> lock(mut);
			++count;
		}
		virtual unsigned GetID() const
		{
			return 0;
		}
		virtual Task* Clone()
		{
			return new TestTask( *this );
		}
		virtual bool isDone()
		{
			return true;
		}
	};

	class TestProc : public ClientMessageProcessorInterface
	{
	public:
		virtual void SendEchoMessage( const std::string& messag ) {}
		virtual void SendRegisterMessage() {};
		virtual	void SendTaskMessage( const unsigned long time, TaskPtr &task ) {};
		virtual	void SendRequesTaskMessage( const unsigned long num ){};
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
		TestTask *task =  new ClientTaskPlannerTest::TestTask();
		TaskPtr taskptr( task );
		TS_ASSERT_EQUALS( task->count, unsigned(0) );
		planner.AddTask( taskptr );
		planner.AddTask( taskptr );
		planner.AddTask( taskptr );
		planner.AddTask( taskptr );
		planner.Run();
		Sleep(300);
		planner.Stop();
		TS_ASSERT_EQUALS( task->count, unsigned(4) );
	}

};

#endif /*CLIENTTASKPLANNERTEST_H_*/
