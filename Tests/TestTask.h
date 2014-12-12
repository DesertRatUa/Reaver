#ifndef TESTTASKU_H_
#define TESTTASKU_H_

#include <cxxtest/TestSuite.h>
#include "Tasks\Task.h"

class UnitTestTask : public CxxTest::TestSuite
{
public:

	class TestTask : public Task
	{
	public:
		TestTask( unsigned PlannerID ) : Task( PlannerID ) {};
		TestTask() {};

		virtual void _SerializeRequest( tinyxml2::XMLDocument &doc ) const {};
		virtual void _DeserializeRequest( const tinyxml2::XMLDocument &doc ) {};

		virtual void _SerializeRespond( tinyxml2::XMLDocument &doc ) const {};
		virtual void _DeserializeRespond( const tinyxml2::XMLDocument &doc ) {};

		virtual void Process() {};
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
			return false;
		}
		virtual Tasks SeperateTask( const unsigned threadNums, const unsigned plannerID ) const
		{
			return Tasks();
		}
	};

	void testRequest()
	{
		TestTask task(1234);
		tinyxml2::XMLDocument doc;
		XMLUtils::AddPacketId( doc, 1 );

		task.SerializeRequest(doc);
		std::string xml = XMLUtils::XMLtoStr( doc );

		doc.Clear();
		doc.Parse( xml.c_str(), xml.length() );

		TestTask task1;
		task1.DeserializeRequest( doc );
		TS_ASSERT_EQUALS( task1.GetPlannerID(), task.GetPlannerID() );
	}

	void testRespond()
	{
		TestTask task(1234);
		tinyxml2::XMLDocument doc;
		XMLUtils::AddPacketId( doc, 1 );

		task.SerializeRespond(doc);
		std::string xml = XMLUtils::XMLtoStr( doc );

		doc.Clear();
		doc.Parse( xml.c_str(), xml.length() );

		TestTask task1;
		task1.DeserializeRespond( doc );
		TS_ASSERT_EQUALS( task1.GetPlannerID(), task.GetPlannerID() );
	}

	void testPlannerID()
	{
		unsigned value = 1234;
		TestTask task(value);
		TS_ASSERT_EQUALS( value, task.GetPlannerID() );
	}

};

#endif /*TESTTASK_H_*/
