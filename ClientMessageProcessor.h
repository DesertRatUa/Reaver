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

	void SendEchoMessage( const std::string& messag );
	void SendRegisterMessage();
	void SendTaskMessage( const unsigned time );

protected:
	static void RecieveEchoMessage( const tinyxml2::XMLDocument& doc, const std::string& addr );
	static void RecieveRegisterMessage( const tinyxml2::XMLDocument& doc, const std::string& addr );
	static void ReciveTaskMessage( const tinyxml2::XMLDocument& doc, const std::string& addr );

	static ClientModule *m_parent;
};

#endif /* CLIENTMESSAGEPROCESSOR_H_ */
