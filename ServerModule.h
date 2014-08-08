/*
 * ServerModule.h
 *
 *  Created on: 13 черв. 2014
 *      Author: maximm
 */

#ifndef SERVERMODULE_H_
#define SERVERMODULE_H_

#include "CommunicationServer.h"
#include "SignalHandler.h"
#include "Module.h"
#include "ServerMessageProcessor.h"

class ServerModule : public Module
{
public:
	ServerModule( Config &config, ArgumentsMap &arguments );
	virtual ~ServerModule();

	virtual void Init();
	virtual void Run();

	void EchoPrc( const std::string& message, const std::string& addr );

protected:
	friend class ServerMessageProcessor;

	CommunicationServer m_connection;
	SignalHandler m_signal;
	ServerMessageProcessor m_processor;
};

#endif /* SERVERMODULE_H_ */
