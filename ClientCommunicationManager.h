/*
 * ComunnicationClient.h
 *
 *  Created on: 23 лип. 2014
 *      Author: maximm
 */

#ifndef COMUNNICATIONCLIENT_H_
#define COMUNNICATIONCLIENT_H_

#include "include.h"
#include "CommunicationManager.h"

class ClientCommunicationManager: public CommunicationManager
{
public:
	ClientCommunicationManager( MessageProcessor &processor, bool &isRun );
	virtual ~ClientCommunicationManager();

	void Connect( const std::string &addr, const unsigned port ) throw(std::runtime_error);
	void Send( const std::string &message );
	void SendRequest( const Message &message );
	void SendRespond( const Message &message );

protected:
	static void DataHandlerThread( ClientCommunicationManager &parent );
};

#endif /* COMUNNICATIONCLIENT_H_ */
