/*
 * SignalHandler.h
 *
 *  Created on: 10 лип. 2014
 *      Author: maximm
 */

#ifndef SIGNALHANDLER_H_
#define SIGNALHANDLER_H_

class SignalHandler
{
public:
	SignalHandler( bool &isRun );
	virtual ~SignalHandler();
	void Init();
	void Wait();

protected:
	bool &m_run;
};

#endif /* SIGNALHANDLER_H_ */
