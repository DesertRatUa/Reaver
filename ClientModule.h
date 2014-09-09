/*
 * ClientModule.h
 *
 *  Created on: 11 лип. 2014
 *      Author: maximm
 */

#ifndef CLIENTMODULE_H_
#define CLIENTMODULE_H_

#include "Module.h"
#include "ClientCommunicationManager.h"
#include "SignalHandler.h"
#include "ClientMessageProcessor.h"

class Task;

class ClientModule : public Module
{
public:
	ClientModule( Config &config, ArgumentsMap &arguments );
	virtual ~ClientModule();

	virtual void Init();
	virtual void Run();

	void ConnectionRespond();
	void RegisterRespond();
	void TaskRequest( TaskPtr &task );

protected:
	friend class ClientMessageProcessor;

	enum State
	{
		FAILED = 0,
		INIT = 1,
		TEST_CONNECTION = 2,
		REGISTER_CLIENT = 3,
		WAIT_FOR_TASK = 4,
	} m_state;

	bool m_run;
	bool m_respond;
	ClientCommunicationManager m_connection;
	SignalHandler m_signal;
	ClientMessageProcessor m_processor;
	unsigned long m_respondTime;
	pthread_mutex_t m_mut;
	pthread_t m_sequence;
	unsigned m_count;

	void Respond();
	void Wait();
	void Stop();
	void RegisterClient();
	void TestConnection();

	void RunSequence();
	static void* SequenceThread( void *arg );
};

#endif /* CLIENTMODULE_H_ */
