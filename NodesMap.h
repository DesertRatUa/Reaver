/*
 * NodesMap.h
 *
 *  Created on: 10 сент. 2014 г.
 *      Author: maximm
 */

#ifndef NODESMAP_H_
#define NODESMAP_H_

#include "include.h"
#include <vector>
#include "Node.h"
#include <mutex>

class NodesMap
{
public:
	NodesMap();
	virtual ~NodesMap();

	void Init();

	void RegisterNode( const Client& client, const unsigned threadNum, ServerMessageProcessorInterface &manager ) throw ( std::exception );
	void UnregisterNode( const Client& client ) throw ( std::exception );
	Node& GetNode( const Client& client ) throw ( std::exception );
	unsigned GetThreadsCount() const;
	void TaskComplete( const Client& client, const TaskPtr &task );

protected:
	typedef std::vector<Node> Nodes;
	Nodes m_nodes;
	mutable std::mutex m_mut;
};

#endif /* NODESMAP_H_ */
