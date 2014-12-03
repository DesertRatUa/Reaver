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
#include "tinyxml2.h"
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
