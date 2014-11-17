/*
 * Client.h
 *
 *  Created on: 01 рту. 2014 у.
 *      Author: maximm
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include "include.h"
#include "Thread.h"
#ifdef WIN32
   #include <winsock2.h>
#else
   #include <sys/socket.h>
   #include <sys/un.h>
#endif

class Client
{
public:
	Client();
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
	SOCKET socket;
	ThreadPtr thread;
	std::mutex m_mut;
};

typedef std::shared_ptr<Client> ClientPtr;

#endif /* CLIENT_H_ */
