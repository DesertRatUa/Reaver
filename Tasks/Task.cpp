/*
 * Task.cpp
 *
 *  Created on: 08 ����. 2014 �.
 *      Author: maximm
 */

#include "Tasks/Task.h"
#include "TestTask.h"

Task::Task()
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
