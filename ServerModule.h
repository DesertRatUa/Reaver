/*
 * ServerModule.h
 *
 *  Created on: 13 черв. 2014
 *      Author: maximm
 */

#ifndef SERVERMODULE_H_
#define SERVERMODULE_H_

#include "include.h"
#include "Thread.h"
#include "ServerCommunicationManager.h"
#include "SignalHandler.h"
#include "Module.h"
#include "ServerMessageProcessor.h"
#include "NodesMap.h"
#include "ServerTaskPlanner.h"

class Task;

class ServerModule : public Module
{
public:
	ServerModule( Config &config, ArgumentsMap &arguments );
	virtual ~ServerModule();

	virtual void Init();
	virtual void Run();

	void RegisterNode( const std::string& addr, const unsigned threadNum );
	void UnregisterNode( const std::string& addr );
	void TaskRespond( const std::string& addr, const TaskPtr &task );
	void TaskRequest( const std::string& addr, const unsigned count );

protected:
	void Stop();

	static void TaskPlannerThread ( ServerModule &parent );
	void _TaskPlanner();

	friend class ServerMessageProcessor;
	bool m_run;
	ServerCommunicationManager m_connection;
	SignalHandler m_signal;
	ServerMessageProcessor m_processor;
	NodesMap m_nodes;
	ServerTaskPlanner m_planner;

	ThreadPtr m_taskPlanner;
};

#endif /* SERVERMODULE_H_ */
