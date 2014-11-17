/*
 * ClientMessageProcessor.h
 *
 *  Created on: 08 рту. 2014 у.
 *      Author: maximm
 */

#ifndef CLIENTMESSAGEPROCESSOR_H_
#define CLIENTMESSAGEPROCESSOR_H_

#include "include.h"
#include "MessageProcessor.h"
#include "Tasks/Task.h"

class ClientMessageProcessorInterface
{
public:
	ClientMessageProcessorInterface();
	virtual ~ClientMessageProcessorInterface();

	virtual void SendEchoMessage( const std::string& messag ) = 0;
	virtual void SendRegisterMessage() = 0;
	virtual	void SendTaskMessage( const unsigned long time, TaskPtr &task ) = 0;
};

class ClientMessageProcessor: public MessageProcessor, public ClientMessageProcessorInterface
{
public:
	ClientMessageProcessor( ClientModule &parent, ClientCommunicationManagerInterface &communication );
	virtual ~ClientMessageProcessor();

	virtual void Init();

	virtual void SendEchoMessage( const std::string& messag );
	virtual void SendRegisterMessage();
	virtual void SendTaskMessage( const unsigned long time, TaskPtr &task );

protected:
	static void RecieveEchoMessage( const tinyxml2::XMLDocument& doc, const std::string& addr );
	static void RecieveRegisterMessage( const tinyxml2::XMLDocument& doc, const std::string& addr );
	static void ReciveTaskMessage( const tinyxml2::XMLDocument& doc, const std::string& addr );

	static ClientCommunicationManagerInterface *m_communication;
	static ClientModule *m_parent;
};

#endif /* CLIENTMESSAGEPROCESSOR_H_ */
