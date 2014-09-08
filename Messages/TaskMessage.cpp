/*
 * TaskMessage.cpp
 *
 *  Created on: 04 сент. 2014 г.
 *      Author: maximm
 */

#include <Messages/TaskMessage.h>
#include <tinyxml2.h>
#include "Tasks/Task.h"

TaskMessage::TaskMessage() : SpendTime(0)
{
}

TaskMessage::TaskMessage( const unsigned spendTime ) : SpendTime( spendTime )
{
}

TaskMessage::TaskMessage( Task &tsk ): SpendTime(0), task( &tsk )
{
}

TaskMessage::~TaskMessage()
{
}

void TaskMessage::_SerializeReqest( tinyxml2::XMLDocument &doc ) const
{
	AddPacketId( doc, 3 );
	if ( task.get() )
	{
		AddNum( doc, "TaskID", task->GetID() );
		task->SerializeRequest( doc );
	}
}

void TaskMessage::_SerializeRespond( tinyxml2::XMLDocument &doc ) const
{
	AddPacketId( doc, 3 );
	AddNum( doc, "SpendTime", SpendTime );
}

void TaskMessage::DeserializeReqest( const tinyxml2::XMLDocument &doc )
{
	const tinyxml2::XMLElement *taskID = doc.FirstChildElement( "TaskID" );
	if ( taskID )
	{
		task.reset( Task::CreateTask( atoi( taskID->GetText() ) ) );
		task->DeserializeRequest( doc );
	}
}

void TaskMessage::DeserializeRespond( const tinyxml2::XMLDocument &doc )
{
	const tinyxml2::XMLElement *time = doc.FirstChildElement( "SpendTime" );
	if ( time )
	{
		SpendTime = atoi( time->GetText() );
	}
}
