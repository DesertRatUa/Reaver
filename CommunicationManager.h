/*
 * CommunicationManager.h
 *
 *  Created on: 13 черв. 2014
 *      Author: maximm
 */

#ifndef COMMUNICATIONMANAGER_H_
#define COMMUNICATIONMANAGER_H_

#include <string>
#include <vector>
//#ifdef WIN32
   #include <winsock2.h>
//#else
   //#include <sys/socket.h>
   //#include <sys/un.h>
//#endif
#include <pthread.h>

class MessageProcessor;

class CommunicationManager
{
public:
	CommunicationManager( MessageProcessor &processor, bool &isRun );
	virtual ~CommunicationManager();

	virtual void Init();
	void Close();

protected:
	static void ReadSocket( SOCKET &socket, CommunicationManager *manager, const std::string &addr );
	virtual void CloseAdditionalThreads();

	MessageProcessor &m_processor;

	bool &m_run;
	WSADATA m_wsaData;
	SOCKET m_socket;
	pthread_t m_mainThread;
	timeval m_timeout;
	sockaddr_in m_address;
};

#endif /* COMMUNICATIONMANAGER_H_ */
