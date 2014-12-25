/*
 * TaskMessage.cpp
 *
 *  Created on: 04 ����. 2014 �.
 *      Author: maximm
 */

#include "Messages/TaskMessage.h"
#include "XMLUtils.h"
#include "Tasks/Task.h"
#include <assert.h>

TaskMessage::TaskMessage() : SpendTime(0), Cancel( false ), PlannerID(0)
{
}

TaskMessage::TaskMessage( const unsigned spendTime, const TaskPtr &tsk ) :
		SpendTime( spendTime ),  Task( tsk ), Cancel( false ), PlannerID(0)
{
}

TaskMessage::TaskMessage( const TaskPtr &tsk ):
		SpendTime(0), Task( tsk ), Cancel( false ), PlannerID(0)
{
}

TaskMessage::TaskMessage( const bool canceled, const unsigned plannerId ) :
		SpendTime(0), Cancel( canceled ), PlannerID( plannerId )
{
}

TaskMessage::~TaskMessage()
{
}

void TaskMessage::SerializeReqest( tinyxml2::XMLDocument &doc ) const
{
	assert( Task.get() );
	XMLUtils::AddPacketId( doc, 3 );
	XMLUtils::AddBool( doc, "Cancel", Cancel );
	XMLUtils::AddInt( doc, "PlannerID", Task->GetPlannerID() );
	if ( !Cancel )
	{
		XMLUtils::AddInt( doc, "TaskID", Task->GetID() );
		Task->SerializeRequest( doc );
	}
}

void TaskMessage::SerializeRespond( tinyxml2::XMLDocument &doc ) const
{
	assert( Task.get() );
	XMLUtils::AddPacketId( doc, 3 );
	XMLUtils::AddBool( doc, "Cancel", Cancel );
	XMLUtils::AddInt( doc, "PlannerID", Task->GetPlannerID() );
	if ( !Cancel )
	{
		XMLUtils::AddInt( doc, "SpendTime", SpendTime );
		XMLUtils::AddInt( doc, "TaskID", Task->GetID() );
		Task->SerializeRespond( doc );
	}
}

void TaskMessage::DeserializeReqest( const tinyxml2::XMLDocument &doc )
{
	XMLUtils::GetBool( doc, "Cancel", Cancel );
	XMLUtils::GetInt( doc, "PlannerID", PlannerID );
	if ( !Cancel )
	{
		unsigned taskId = 0;
		XMLUtils::GetInt( doc, "TaskID", taskId );
		if ( taskId != 0 )
		{
			Task.reset( Task::CreateTask( taskId ) );
			assert( Task.get() );
			Task->DeserializeRequest( doc );
		}
	}
}

void TaskMessage::DeserializeRespond( const tinyxml2::XMLDocument &doc )
{
	XMLUtils::GetBool( doc, "Cancel", Cancel );
	XMLUtils::GetInt( doc, "PlannerID", PlannerID );
	if ( !Cancel )
	{
		unsigned taskId = 0;
		XMLUtils::GetInt( doc, "SpendTime", SpendTime );
		XMLUtils::GetInt( doc, "TaskID", taskId );
		if ( taskId != 0 )
		{
			Task.reset( Task::CreateTask( taskId ) );
			assert( Task.get() );
			Task->DeserializeRespond( doc );
		}
	}
}
