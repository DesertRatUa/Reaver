/*
 * TaskMessage.h
 *
 *  Created on: 04 сент. 2014 г.
 *      Author: maximm
 */

#ifndef TASKMESSAGE_H_
#define TASKMESSAGE_H_

#include "Messages/Message.h"
#include "Tasks/Task.h"
#include "memory"

class TaskMessage: public Message
{
public:
	TaskMessage();
	TaskMessage( const unsigned spendTime, const TaskPtr &tsk );
	TaskMessage( const TaskPtr &tsk );
	TaskMessage( const bool canceled, const unsigned plannerId );
	virtual ~TaskMessage();

	virtual void SerializeReqest( tinyxml2::XMLDocument &doc ) const;
	virtual void SerializeRespond( tinyxml2::XMLDocument &doc ) const;
	virtual void DeserializeReqest( const tinyxml2::XMLDocument &doc );
	virtual void DeserializeRespond( const tinyxml2::XMLDocument &doc );

	bool Cancel;
	unsigned SpendTime;
	unsigned PlannerID;
	TaskPtr Task;
};

#endif /* TASKMESSAGE_H_ */
