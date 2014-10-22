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
	TaskMessage( const unsigned spendTime, TaskPtr &tsk );
	TaskMessage( TaskPtr &tsk );
	virtual ~TaskMessage();

	virtual void _SerializeReqest( tinyxml2::XMLDocument &doc ) const;
	virtual void _SerializeRespond( tinyxml2::XMLDocument &doc ) const;
	virtual void DeserializeReqest( const tinyxml2::XMLDocument &doc );
	virtual void DeserializeRespond( const tinyxml2::XMLDocument &doc );

	unsigned SpendTime;
	std::shared_ptr<Task> task;
};

#endif /* TASKMESSAGE_H_ */
