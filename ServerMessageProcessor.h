/*
 * ServerMessageProcessor.h
 *
 *  Created on: 08 рту. 2014 у.
 *      Author: maximm
 */

#ifndef SERVERMESSAGEPROCESSOR_H_
#define SERVERMESSAGEPROCESSOR_H_

#include "ServerMessageProcessorInterface.h"

class ServerMessageProcessor : public ServerMessageProcessorInterface
{
public:
	ServerMessageProcessor( ServerModule *parent );
	virtual ~ServerMessageProcessor();

	virtual void Init();
	virtual void SendRegisterMessage( const std::string &addr, const std::string *error );
	virtual void SendTaskMessage( const std::string &addr, TaskPtr &task );

protected:
	static ServerModule *m_parent;
	static void RecieveEchoMessage( const tinyxml2::XMLDocument& doc, const std::string& addr );
	static void RecieveRegisterMessage( const tinyxml2::XMLDocument& doc, const std::string& addr );
	static void RecieveTaskMessage( const tinyxml2::XMLDocument& doc, const std::string& addr );
};

#endif /* SERVERMESSAGEPROCESSOR_H_ */
