/*
 * CommunicationManager.h
 *
 *  Created on: 13 черв. 2014
 *      Author: maximm
 */

#ifndef COMMUNICATIONMANAGER_H_
#define COMMUNICATIONMANAGER_H_

#include <string>

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
};

#endif /* COMMUNICATIONMANAGER_H_ */
