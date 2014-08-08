/*
 * ClientModule.h
 *
 *  Created on: 11 лип. 2014
 *      Author: maximm
 */

#ifndef CLIENTMODULE_H_
#define CLIENTMODULE_H_

#include "Module.h"
#include "CommunicationClient.h"
#include "SignalHandler.h"
#include "ClientMessageProcessor.h"

class ClientModule : public Module
{
public:
	ClientModule( Config &config, ArgumentsMap &arguments );
	virtual ~ClientModule();

	virtual void Init();
	virtual void Run();

protected:
	friend class ClientMessageProcessor;

	CommunicationClient m_connection;
	SignalHandler m_signal;
	ClientMessageProcessor m_processor;
};

#endif /* CLIENTMODULE_H_ */
