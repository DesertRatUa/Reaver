/*
 * ClientModule.h
 *
 *  Created on: 11 лип. 2014
 *      Author: maximm
 */

#ifndef CLIENTMODULE_H_
#define CLIENTMODULE_H_

#include "Module.h"
#include "CommunicationManager.h"
#include "SignalHandler.h"

class ClientModule : public Module
{
public:
	ClientModule( Config &config, ArgumentsMap &arguments );
	virtual ~ClientModule();

	virtual void Init();
	virtual void Run();

protected:
	CommunicationManager m_connection;
	SignalHandler m_signal;
};

#endif /* CLIENTMODULE_H_ */
