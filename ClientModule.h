/*
 * ClientModule.h
 *
 *  Created on: 11 лип. 2014
 *      Author: maximm
 */

#ifndef CLIENTMODULE_H_
#define CLIENTMODULE_H_

#include "include.h"
#include "Module.h"
#include "ClientCommunicationManager.h"
#include "SignalHandler.h"
#include "ClientMessageProcessor.h"
#include <mutex>

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
	std::mutex m_mut;
	std::auto_ptr<std::thread> m_sequence;
	unsigned m_count;

	void Respond();
	void Wait();
	void Stop();
	void RegisterClient();
	void TestConnection();

	static void SequenceThread( ClientModule &parent );
};

#endif /* CLIENTMODULE_H_ */
