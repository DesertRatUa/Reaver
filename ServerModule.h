/*
 * ServerModule.h
 *
 *  Created on: 13 черв. 2014
 *      Author: maximm
 */

#ifndef SERVERMODULE_H_
#define SERVERMODULE_H_

#include "Config.h"
#include "ArgumentsMap.h"
#include "CommunicationManager.h"

class ServerModule
{
public:
	ServerModule( Config &config, ArgumentsMap &arguments );
	virtual ~ServerModule();

	void Init();
	void Run();

protected:
	Config &m_config;
	ArgumentsMap &m_arguments;
	CommunicationManager m_connection;
};

#endif /* SERVERMODULE_H_ */
