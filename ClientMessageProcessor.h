/*
 * ClientMessageProcessor.h
 *
 *  Created on: 08 рту. 2014 у.
 *      Author: maximm
 */

#ifndef CLIENTMESSAGEPROCESSOR_H_
#define CLIENTMESSAGEPROCESSOR_H_

#include "MessageProcessor.h"

class ClientModule;

class ClientMessageProcessor: public MessageProcessor
{
public:
	ClientMessageProcessor( ClientModule *parent );
	virtual ~ClientMessageProcessor();

	virtual void Init();

	void SendEchomMessage( const std::string& messag );

protected:
	static void RecieveEchoMessage( const std::string& message, const std::string& addr );

	static ClientModule *m_parent;
};

#endif /* CLIENTMESSAGEPROCESSOR_H_ */
