/*
 * ServerMessageProcessor.h
 *
 *  Created on: 08 рту. 2014 у.
 *      Author: maximm
 */

#ifndef SERVERMESSAGEPROCESSOR_H_
#define SERVERMESSAGEPROCESSOR_H_
#include "MessageProcessor.h"

class ServerModule;

class ServerMessageProcessor : public MessageProcessor
{
public:
	ServerMessageProcessor( ServerModule *parent );
	virtual ~ServerMessageProcessor();

	virtual void Init();
	void SendRegisterMessage( const std::string &addr, const unsigned id, const std::string *error );

protected:
	static ServerModule *m_parent;
	static void RecieveEchoMessage( const tinyxml2::XMLDocument& doc, const std::string& addr );
	static void RecieveRegisterMessage( const tinyxml2::XMLDocument& doc, const std::string& addr );
};

#endif /* SERVERMESSAGEPROCESSOR_H_ */
