/*
 * ComunnicationClient.h
 *
 *  Created on: 23 лип. 2014
 *      Author: maximm
 */

#ifndef COMUNNICATIONCLIENT_H_
#define COMUNNICATIONCLIENT_H_

#include "CommunicationManager.h"

class ClientCommunicationManager: public CommunicationManager
{
public:
	ClientCommunicationManager( MessageProcessor &processor, bool &isRun );
	virtual ~ClientCommunicationManager();

	void Connect( const std::string &addr, const unsigned port );
	void Send( const std::string &message );

private:
	static void *DataHandlerThr( void *arg );
};

#endif /* COMUNNICATIONCLIENT_H_ */
