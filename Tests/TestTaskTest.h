#ifndef TESTTASKTEST_H_
#define TESTTASKTEST_H_

#include <cxxtest/TestSuite.h>

#include "Tasks\TestTask.h"

class TestTaskTest : public CxxTest::TestSuite
{
public:
	void testProcess()
	{
		TestTask task( 1, 10, 8 );
		task.Process();
		TS_ASSERT_EQUALS( task.result, unsigned( 8 ) );
	}

	void testSeperateTask()
	{
		/*
		TestTask task( 1, 15, 8 );
		Tasks tasks( task.SeperateTask( 3, 1 ) );
		TS_ASSERT_EQUALS( tasks.size(), unsigned( 3 ) );
		TS_ASSERT_EQUALS( tasks.front()->m_plannerID, unsigned( 1 ) );
		*/
	}

};

#endif /*TESTTASKTEST_H_*/
