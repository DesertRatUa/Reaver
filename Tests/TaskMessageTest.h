#ifndef TASKMESSAGETEST_H_
#define TASKMESSAGETEST_H_

#include <cxxtest/TestSuite.h>
#include "Tasks\TestTask.h"
#include "Messages\TaskMessage.h"

class TaskMessageTest : public CxxTest::TestSuite
{
public:

	void testRequest()
	{
		TaskPtr task( new TestTask() );
		task->m_plannerID = 3345;
		TaskMessage mes1( task );
		std::string xml = mes1.SerializeReqestStr();

		TaskMessage mes2;
		mes2.DeserializeReqestStr( xml );

		TS_ASSERT_EQUALS( mes1.Cancel, false );
		TS_ASSERT_EQUALS( mes1.Cancel, mes2.Cancel );
		TS_ASSERT_EQUALS( task->m_plannerID, mes2.PlannerID );
		TS_ASSERT( mes2.Task.get() != NULL );
		TS_ASSERT_EQUALS( mes2.Task->GetID(), task->GetID() );
	}

	void testRequestCancel()
	{
		TaskPtr task( new TestTask() );
		task->m_plannerID = 3345;
		TaskMessage mes1( task );
		mes1.Cancel = true;
		std::string xml = mes1.SerializeReqestStr();

		TaskMessage mes2;
		mes2.DeserializeReqestStr( xml );
		TS_ASSERT_EQUALS( mes1.Cancel, true );
		TS_ASSERT_EQUALS( mes1.Cancel, mes2.Cancel );
		TS_ASSERT_EQUALS( task->m_plannerID, mes2.PlannerID );
		TS_ASSERT( mes2.Task.get() == NULL );
	}

	void testRespond()
	{
		TaskPtr task( new TestTask() );
		task->m_plannerID = 3345;
		TaskMessage mes1( task );
		mes1.SpendTime = 2131312;
		std::string xml = mes1.SerializeRespondStr();

		TaskMessage mes2;
		mes2.DeserializeRespondStr( xml );
		TS_ASSERT_EQUALS( mes1.Cancel, false );
		TS_ASSERT_EQUALS( mes1.Cancel, mes2.Cancel );
		TS_ASSERT_EQUALS( task->m_plannerID, mes2.PlannerID );
		TS_ASSERT_EQUALS( mes1.SpendTime, mes2.SpendTime );
		TS_ASSERT( mes2.Task.get() != NULL );
		TS_ASSERT_EQUALS( mes2.Task->GetID(), task->GetID() );
	}

	void testRespondCancel()
	{
		TaskPtr task( new TestTask() );
		task->m_plannerID = 3345;
		TaskMessage mes1( task );
		mes1.Cancel = true;
		std::string xml = mes1.SerializeRespondStr();

		TaskMessage mes2;
		mes2.DeserializeRespondStr( xml );
		TS_ASSERT_EQUALS( mes1.Cancel, mes2.Cancel );
		TS_ASSERT_EQUALS( task->m_plannerID, mes2.PlannerID );
		TS_ASSERT( mes2.Task.get() == NULL );
	}
};

#endif /*TASKMESSAGETEST_H_*/
