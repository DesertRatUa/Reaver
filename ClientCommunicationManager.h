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
#include "Thread.h"

class ClientCommunicationManagerInterface
{
public:
	ClientCommunicationManagerInterface();
	virtual ~ClientCommunicationManagerInterface();

	virtual void SendRequest( const Message &message ) = 0;
	virtual	void SendRespond( const Message &message ) = 0;
};

class ClientCommunicationManager: public CommunicationManager, public ClientCommunicationManagerInterface
{
public:
	ClientCommunicationManager( MessageProcessor &processor, bool &isRun );
	virtual ~ClientCommunicationManager();

	void Connect( const std::string &addr, const unsigned port ) throw(std::runtime_error);

	virtual void SendRequest( const Message &message );
	virtual void SendRespond( const Message &message );

protected:
	void Send( const std::string &message );
	static void DataHandlerThread( ClientCommunicationManager &parent );

	std::mutex m_mut;
};

#endif /* COMUNNICATIONCLIENT_H_ */
