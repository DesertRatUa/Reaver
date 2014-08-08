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

protected:
	static ServerModule *m_parent;
	static void RecieveEchoMessage( const std::string& message, const std::string& addr );
};

#endif /* SERVERMESSAGEPROCESSOR_H_ */
