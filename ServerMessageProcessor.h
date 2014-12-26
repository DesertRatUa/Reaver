/*
 * ServerMessageProcessor.h
 *
 *  Created on: 08 рту. 2014 у.
 *      Author: maximm
 */

#ifndef SERVERMESSAGEPROCESSOR_H_
#define SERVERMESSAGEPROCESSOR_H_

#include "include.h"
#include "MessageProcessor.h"
#include "Tasks/Task.h"
#include "Client.h"

class ServerMessageProcessorInterface : public MessageProcessor
{
public:
	ServerMessageProcessorInterface();
	virtual ~ServerMessageProcessorInterface();

	virtual void SendRegisterMessage( const Client &client, const std::string *error ) = 0;
	virtual void SendTaskMessage( const Client &client, const TaskPtr &task ) = 0;
	virtual void SendCancelTaskMessage( const Client &client, const unsigned plannerId ) = 0;
};

class ServerMessageProcessor : public ServerMessageProcessorInterface
{
public:
	ServerMessageProcessor( ServerModule *parent );
	virtual ~ServerMessageProcessor();

	virtual void Init();
	virtual void SendRegisterMessage( const Client &client, const std::string *error );
	virtual void SendTaskMessage( const Client &client, const TaskPtr &task );
	virtual void SendCancelTaskMessage( const Client &client, const unsigned plannerId );

protected:
	static ServerModule *m_parent;
	static void RecieveEchoMessage( const tinyxml2::XMLDocument& doc, const std::string& addr );
	static void RecieveRegisterMessage( const tinyxml2::XMLDocument& doc, const std::string& addr );
	static void RecieveTaskMessage( const tinyxml2::XMLDocument& doc, const std::string& addr );
	static void RecieveRequesTaskMessage( const tinyxml2::XMLDocument& doc, const std::string& addr );
};

#endif /* SERVERMESSAGEPROCESSOR_H_ */
