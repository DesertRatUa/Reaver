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

	void UpdateState();
	void TestConnection();
	void ConnectionRespond();
	void RegisterClient();
	void Stop();

protected:
	friend class ClientMessageProcessor;

	enum State
	{
		FAILED = 0,
		TEST_CONNECTION = 1,
		WAIT_CONNECTION = 2,
		REGISTER_CLIENT = 3,
		WAIT_REGISTER = 4,
		DONE = 5,
	} m_state;

	bool m_run;
	ClientCommunicationManager m_connection;
	SignalHandler m_signal;
	ClientMessageProcessor m_processor;
	unsigned long m_respondTime;
};

#endif /* CLIENTMODULE_H_ */
