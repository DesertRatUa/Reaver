/*
 * Client.h
 *
 *  Created on: 01 рту. 2014 у.
 *      Author: maximm
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include "include.h"
#include <winsock2.h>
#include <thread>

class ServerCommunicationManager;

class Client
{
public:
	Client( ServerCommunicationManager&Manager );
	virtual ~Client();

	void Send( const std::string& message );
	void SendRequest( const Message& message );
	void SendRespond( const Message& message );
	void Disconnect();
	void Join();
	bool isDisconnected();
	std::string GetAddr();


	sockaddr_in addr;

	bool operator==( const Client &client ) const;

protected:

	bool m_disconnected;
	friend class ServerCommunicationManager;
	ServerCommunicationManager &manager;
	SOCKET socket;
	std::unique_ptr<std::thread> thread;
};

typedef std::shared_ptr<Client> ClientPtr;

#endif /* CLIENT_H_ */
