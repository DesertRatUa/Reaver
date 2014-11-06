#ifndef TASKPLANNERTEST_H_
#define TASKPLANNERTEST_H_

#include <cxxtest/TestSuite.h>

#define protected public
#include "TaskPlanner.h"
#undef protected

class TaskPlannerTest : public CxxTest::TestSuite
{
	class TestTask : public Task
	{
		virtual void SerializeRequest( tinyxml2::XMLDocument &doc ) const {}
		virtual void DeserializeRequest( const tinyxml2::XMLDocument &doc )  {}
		virtual void SerializeRespond( tinyxml2::XMLDocument &doc ) const {}
		virtual void DeserializeRespond( const tinyxml2::XMLDocument &doc ) {}
		virtual Tasks SeperateTask( const unsigned threadNums, const unsigned plannerID ) const
		{
			Tasks tasks;
			for( unsigned i = 0; i < threadNums; ++i )
			{
				tasks.push_back( TaskPtr( new TestTask() ) );
				tasks.back()->m_plannerID = plannerID;
			}

			return tasks;
		}
		virtual void Process() {}
		virtual unsigned GetID() const
		{
			return 0;
		}
	};

public:
	void testAddTask()
	{
		TaskPlanner planner;
		TaskPtr task( new TestTask() );
		planner.AddTask( task, 2 );
		TS_ASSERT_EQUALS( planner.m_tasks.size(), unsigned(2) );
		TS_ASSERT_EQUALS( planner.m_tasks.front()->m_plannerID , unsigned(1) );
		planner.AddTask( task, 2 );
		TS_ASSERT_EQUALS( planner.m_tasks.back()->m_plannerID , unsigned(2) );
	}

	void testTaskComplete()
	{
		TaskPlanner planner;
		TaskPtr task( new TestTask() );
		planner.AddTask( task, 2 );
		planner.AddTask( task, 3 );
		task->m_plannerID = 1;
		planner.TaskComplete( task );
		TS_ASSERT_EQUALS( unsigned (planner.m_tasks.size()), unsigned(3) );
	}

};

#endif /*TASKPLANNERTEST_H_*/
