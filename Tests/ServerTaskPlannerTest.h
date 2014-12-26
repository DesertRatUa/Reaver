#ifndef SERVERTASKPLANNERTEST_H_
#define SERVERTASKPLANNERTEST_H_

#include <cxxtest/TestSuite.h>

#define protected public
#include "ServerTaskPlanner.h"
#include "Tasks/TestTask.h"
#undef protected

class ServerTaskPlannerTest : public CxxTest::TestSuite
{
public:
	void testAddTask()
	{
		TaskPtr task( new TestTask() );
		ServerTaskPlanner planner;
		planner.AddTask( task, 2 );
		TS_ASSERT_EQUALS( planner.m_tasks.size(), unsigned(100) );
	}

	void testTaskComplete()
	{
		TaskPtr task( new TestTask() );
		ServerTaskPlanner planner;
		planner.AddTask( task, 2 );
		task->m_plannerID = 1;
		planner.TaskComplete( task );
		TS_ASSERT_EQUALS( planner.m_tasks.size(), unsigned(0) );
	}

	void testGetTask()
	{
		TaskPtr task( new TestTask() );
		ServerTaskPlanner planner;
		planner.AddTask( task, 2 );
		task->m_plannerID = 1;
		for ( unsigned i = 0; i < 100; ++i )
		{
			TS_ASSERT( planner.GetTask().get() != NULL );
		}
		TS_ASSERT( planner.GetTask().get() == NULL );
	}

};

#endif /*SERVERTASKPLANNERTEST_H_*/
