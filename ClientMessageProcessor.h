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
namespace tinyxml2
{
	class XMLDocument;
}

class ClientMessageProcessor: public MessageProcessor
{
public:
	ClientMessageProcessor( ClientModule *parent );
	virtual ~ClientMessageProcessor();

	virtual void Init();

	void SendEchomMessage( const std::string& messag );

protected:
	static void RecieveEchoMessage( const std::string& message, const std::string& addr );
	static void AddPacketId( tinyxml2::XMLDocument &doc, const unsigned id );
	static void AddText( tinyxml2::XMLDocument &doc, const std::string &name, const std::string &text );

	static ClientModule *m_parent;
};

#endif /* CLIENTMESSAGEPROCESSOR_H_ */
