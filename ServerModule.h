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
#include "NodesMap.h"
#include <auto_ptr.h>

class Task;

namespace std
{
	class thread;
}

class ServerModule : public Module
{
public:
	ServerModule( Config &config, ArgumentsMap &arguments );
	virtual ~ServerModule();

	virtual void Init();
	virtual void Run();

	static void* TaskPlannerThread ( void *arg );
	void TaskPlanner();

	void RegisterNode( const std::string& addr, const unsigned threadNum );
	void UnregisterNode( const std::string& addr );
	void TaskRespond( const std::string& addr, Task &task );

protected:
	void Stop();

	friend class ServerMessageProcessor;
	bool m_run;
	ServerCommunicationManager m_connection;
	SignalHandler m_signal;
	ServerMessageProcessor m_processor;
	NodesMap m_nodes;
	pthread_mutex_t m_mut;

	std::auto_ptr<std::thread> m_taskPlanner;
};

#endif /* SERVERMODULE_H_ */
