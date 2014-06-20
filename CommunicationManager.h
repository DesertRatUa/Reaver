/*
 * CommunicationManager.h
 *
 *  Created on: 13 черв. 2014
 *      Author: maximm
 */

#ifndef COMMUNICATIONMANAGER_H_
#define COMMUNICATIONMANAGER_H_

#include <string>
#ifdef WIN32
   #include <winsock2.h>
#else
   #include <sys/socket.h>
   #include <sys/un.h>
#endif
#include <pthread.h>

class CommunicationManager
{
public:
	CommunicationManager();
	virtual ~CommunicationManager();

	void Init();
	void Connect( const std::string &addr, const unsigned port );
	void Listen( const std::string &addr, const unsigned port );
	void Close();

protected:
	void Update();
	static void *Run( void *arg );

	bool m_run;
	WSADATA m_wsaData;
	SOCKET m_listenSocket;
	pthread_t m_mainThread;
};

#endif /* COMMUNICATIONMANAGER_H_ */
