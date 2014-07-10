/*
 * SignalHandler.h
 *
 *  Created on: 10 лип. 2014
 *      Author: maximm
 */

#ifndef SIGNALHANDLER_H_
#define SIGNALHANDLER_H_

#include <pthread.h>

class SignalHandler
{
public:
	SignalHandler();
	virtual ~SignalHandler();
	void Init();
	void Wait();

protected:
	BOOL CatchHandler( DWORD fdwCtrlTyp );
	static void *Thread( void *parent );
	void Handle();

	pthread_mutex_t m_run;
	pthread_t m_mainThread;
	bool m_handled;
};

#endif /* SIGNALHANDLER_H_ */
