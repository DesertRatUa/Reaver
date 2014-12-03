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

	void RegisterNode( const std::string& addr, const unsigned threadNum, ServerMessageProcessorInterface &manager ) throw ( std::exception );
	void UnregisterNode( const std::string& addr ) throw ( std::exception );
	Node& GetNode( const std::string& addr ) throw ( std::exception );
	Node* GetFreeNode() ;
	unsigned GetFreeThreadsNum();
	void TaskComplete( const std::string& addr, const TaskPtr &task );
	void CheckForStaleTasks( const unsigned timeOut );

protected:
	typedef std::vector<Node> Nodes;
	Nodes m_nodes;
	std::mutex m_mut;
};

#endif /* NODESMAP_H_ */
