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

class ClientModule : public Module
{
public:
	ClientModule( Config &config, ArgumentsMap &arguments );
	virtual ~ClientModule();

	virtual void Init();
	virtual void Run();

	void RunSequence();
	static void* SequenceThread( void *arg );

	void TestConnection();
	void ConnectionRespond();
	void RegisterRespond();
	void RegisterClient();
	void Stop();
	unsigned GetLastTick();
	void Respond();



protected:
	friend class ClientMessageProcessor;

	enum State
	{
		FAILED = 0,
		INIT = 1,
		TEST_CONNECTION = 2,
		REGISTER_CLIENT = 3,
		UNREGISTER_CLIENT = 4,
		DONE = 5,
	} m_state, m_lastState;

	bool m_run;
	ClientCommunicationManager m_connection;
	SignalHandler m_signal;
	ClientMessageProcessor m_processor;
	unsigned long m_respondTime;
	pthread_mutex_t m_mut;
	pthread_t m_sequence;
	unsigned m_count;
};

#endif /* CLIENTMODULE_H_ */
