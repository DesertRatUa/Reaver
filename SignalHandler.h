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
};

#endif /* SIGNALHANDLER_H_ */
