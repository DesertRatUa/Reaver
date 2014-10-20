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
#include <boost/shared_ptr.hpp>
#include <thread>

class ServerCommunicationManager;

namespace std
{
	class thread;
}

class Client
{
public:
	Client( ServerCommunicationManager&Manager );
	virtual ~Client();

	void Send( const std::string& message );
	void SendRequest( const Message& message );
	void SendRespond( const Message& message );
	std::string GetAddr();

	sockaddr_in addr;

	bool operator==( const Client &client ) const;

protected:

	friend class ServerCommunicationManager;
	ServerCommunicationManager &manager;
	SOCKET socket;
	std::unique_ptr<std::thread> thread;
};

typedef boost::shared_ptr<Client> ClientPtr;

#endif /* CLIENT_H_ */
