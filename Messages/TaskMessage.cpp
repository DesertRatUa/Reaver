/*
 * TaskMessage.cpp
 *
 *  Created on: 04 сент. 2014 г.
 *      Author: maximm
 */

#include <Messages/TaskMessage.h>
#include "XMLUtils.h"
#include "Tasks/Task.h"
#include <assert.h>

TaskMessage::TaskMessage() : SpendTime(0)
{
}

TaskMessage::TaskMessage( const unsigned spendTime, TaskPtr &tsk ) : SpendTime( spendTime ),  task( tsk )
{
}

TaskMessage::TaskMessage( TaskPtr &tsk ): SpendTime(0), task( tsk )
{
}

TaskMessage::~TaskMessage()
{
}

void TaskMessage::_SerializeReqest( tinyxml2::XMLDocument &doc ) const
{
	assert( task.get() );
	XMLUtils::AddPacketId( doc, 3 );
	XMLUtils::AddInt( doc, "TaskID", task->GetID() );
	task->SerializeRequest( doc );
}

void TaskMessage::_SerializeRespond( tinyxml2::XMLDocument &doc ) const
{
	assert( task.get() );
	XMLUtils::AddPacketId( doc, 3 );
	XMLUtils::AddInt( doc, "SpendTime", SpendTime );
	XMLUtils::AddInt( doc, "TaskID", task->GetID() );
	task->SerializeRespond( doc );
}

void TaskMessage::DeserializeReqest( const tinyxml2::XMLDocument &doc )
{
	unsigned taskId = 0;
	XMLUtils::GetInt( doc, "TaskID", taskId );
	if ( taskId != 0 )
	{
		task.reset( Task::CreateTask( taskId ) );
		assert( task.get() );
		task->DeserializeRequest( doc );
	}
}

void TaskMessage::DeserializeRespond( const tinyxml2::XMLDocument &doc )
{
	unsigned taskId = 0;
	XMLUtils::GetInt( doc, "SpendTime", SpendTime );
	XMLUtils::GetInt( doc, "TaskID", taskId );
	if ( taskId != 0 )
	{
		task.reset( Task::CreateTask( taskId ) );
		assert( task.get() );
		task->DeserializeRespond( doc );
	}
}
