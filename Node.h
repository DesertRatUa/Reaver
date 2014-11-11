/*
 * Node.h
 *
 *  Created on: 26 ���. 2014 �.
 *      Author: maximm
 */

#ifndef NODE_H_
#define NODE_H_

#include "include.h"
#include "Tasks/Task.h"

class Node
{
public:
	Node( const std::string &addr, const unsigned threadNum, ServerMessageProcessorInterface &manager );
	virtual ~Node();

	bool isThreadsAvalible() const;
	unsigned GetFreeThreadsNum() const;
	std::string GetID() const;

	bool operator==( const Node& node ) const;
	bool operator==( const std::string& addr ) const;

	Node& operator=(const Node& node );

	void SendTask( TaskPtr& task ) throw ( std::exception );
	void TaskComplete() throw ( std::exception );

protected:

	unsigned m_threads;
	unsigned m_threadsLimit;
	std::string m_addr;

	ServerMessageProcessorInterface &m_proccessor;
};

#endif /* NODE_H_ */
