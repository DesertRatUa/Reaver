/*
 * ServerMessageProcessorInterface.h
 *
 *  Created on: 03 но€б. 2014 г.
 *      Author: maximm
 */

#ifndef SERVERMESSAGEPROCESSORINTERFACE_H_
#define SERVERMESSAGEPROCESSORINTERFACE_H_

#include "include.h"
#include "MessageProcessor.h"
#include "Tasks/Task.h"

class ServerMessageProcessorInterface : public MessageProcessor
{
public:
	ServerMessageProcessorInterface();
	virtual ~ServerMessageProcessorInterface();

	virtual void SendRegisterMessage( const std::string &addr, const std::string *error ) = 0;
	virtual void SendTaskMessage( const std::string &addr, TaskPtr &task ) = 0;
};

#endif /* SERVERMESSAGEPROCESSORINTERFACE_H_ */
