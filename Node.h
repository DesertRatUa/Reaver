/*
 * Node.h
 *
 *  Created on: 26 рту. 2014 у.
 *      Author: maximm
 */

#ifndef NODE_H_
#define NODE_H_

#include "include.h"
#include "Tasks/Task.h"
#include <vector>
#include <mutex>

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

	void SendTask( const TaskPtr& task ) throw ( std::exception );
	void TaskComplete( const TaskPtr& task ) throw ( std::exception );
	void CheckForStaleTasks( const unsigned timeOut );

	struct ThreadData
	{
		ThreadData( unsigned long start, unsigned id );
		bool operator==( const unsigned &id ) const;
		unsigned long startTime;
		unsigned plannerID;
	};

protected:
	typedef std::vector<ThreadData> TaskTimes;
	TaskTimes m_times;
	unsigned m_threadsLimit;
	std::string m_addr;
	std::shared_ptr<std::mutex> m_mut;

	ServerMessageProcessorInterface *m_proccessor;
};

#endif /* NODE_H_ */
