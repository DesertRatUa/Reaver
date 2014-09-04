/*
 * TaskMessage.h
 *
 *  Created on: 04 сент. 2014 г.
 *      Author: maximm
 */

#ifndef TASKMESSAGE_H_
#define TASKMESSAGE_H_

#include <Messages/Message.h>

class TaskMessage: public Message
{
public:
	TaskMessage();
	TaskMessage( const unsigned spendTime );
	virtual ~TaskMessage();

	virtual void _SerializeReqest( tinyxml2::XMLDocument &doc ) const;
	virtual void _SerializeRespond( tinyxml2::XMLDocument &doc ) const;
	virtual void DeserializeReqest( const tinyxml2::XMLDocument &doc );
	virtual void DeserializeRespond( const tinyxml2::XMLDocument &doc );

	unsigned SpendTime;
};

#endif /* TASKMESSAGE_H_ */
