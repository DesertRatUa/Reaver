/*
 * ServerModule.h
 *
 *  Created on: 13 черв. 2014
 *      Author: maximm
 */

#ifndef SERVERMODULE_H_
#define SERVERMODULE_H_

#include "ServerCommunicationManager.h"
#include "SignalHandler.h"
#include "Module.h"
#include "ServerMessageProcessor.h"
#include "Node.h"

class ServerModule : public Module
{
public:
	ServerModule( Config &config, ArgumentsMap &arguments );
	virtual ~ServerModule();

	virtual void Init();
	virtual void Run();

	void RegisterNode( const std::string& addr );
	void UnregisterNode( const std::string& addr );
	void TaskRespond( const std::string& addr );

protected:
	friend class ServerMessageProcessor;
	bool m_run;
	ServerCommunicationManager m_connection;
	SignalHandler m_signal;
	ServerMessageProcessor m_processor;
	pthread_mutex_t m_mut;
	unsigned m_nodesID;

	typedef std::vector<Node> Nodes;
	Nodes m_nodes;
};

#endif /* SERVERMODULE_H_ */
