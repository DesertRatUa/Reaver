/*
 * RequestTask.h
 *
 *  Created on: 26 ���. 2014 �.
 *      Author: maximm
 */

#ifndef REQUESTTASK_H_
#define REQUESTTASK_H_

#include <Messages/Message.h>

class RequestTaskMessage: public Message
{
public:
	RequestTaskMessage( const unsigned threads );
	RequestTaskMessage();
	virtual ~RequestTaskMessage();

	virtual void SerializeReqest( tinyxml2::XMLDocument &doc ) const;
	virtual void SerializeRespond( tinyxml2::XMLDocument &doc ) const;
	virtual void DeserializeReqest( const tinyxml2::XMLDocument &doc );
	virtual void DeserializeRespond( const tinyxml2::XMLDocument &doc );

	unsigned m_threads;
};

#endif /* REQUESTTASK_H_ */
