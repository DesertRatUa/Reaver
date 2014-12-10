/*
 * Task.cpp
 *
 *  Created on: 08 сент. 2014 г.
 *      Author: maximm
 */

#define protected public
#include "Tasks/Task.h"
#undef protected

#include "TestTask.h"
#include "XMLUtils.h"
using namespace tinyxml2;

Task::Task() : m_plannerID(0)
{
}

Task::Task( const unsigned plannerId ): m_plannerID(plannerId)
{

}

Task::~Task()
{
}

void Task::SerializeRequest( tinyxml2::XMLDocument &doc ) const
{
	XMLUtils::AddInt( doc, "PlannerId", m_plannerID );
	_SerializeRequest( doc );
}

void Task::DeserializeRequest( const tinyxml2::XMLDocument &doc )
{
	XMLUtils::GetInt( doc, "PlannerId", m_plannerID );
	_DeserializeRequest( doc );
}

void Task::SerializeRespond( tinyxml2::XMLDocument &doc ) const
{
	XMLUtils::AddInt( doc, "PlannerId", m_plannerID );
	_SerializeRespond( doc );
}

void Task::DeserializeRespond( const tinyxml2::XMLDocument &doc )
{
	XMLUtils::GetInt( doc, "PlannerId", m_plannerID );
	_DeserializeRespond( doc );
}

Task* Task::CreateTask( const unsigned id )
{
	switch ( id )
	{
		case 1 : return new TestTask();
		default : return NULL;
	}
}

unsigned Task::GetPlannerID() const
{
	return m_plannerID;
}
