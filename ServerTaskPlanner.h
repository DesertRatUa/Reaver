/*
 * TaskPlanner.h
 *
 *  Created on: 03 но€б. 2014 г.
 *      Author: maximm
 */

#ifndef TASKPLANNER_H_
#define TASKPLANNER_H_

#include "include.h"
#include "Thread.h"
#include "Tasks/Task.h"

class ServerTaskPlanner
{
public:
	ServerTaskPlanner();
	virtual ~ServerTaskPlanner();

	void Init();
	void AddTask( const TaskPtr &task, const unsigned threadsNum );
	void TaskComplete( const TaskPtr &task );
	TaskPtr GetTask();

protected:
	Tasks m_tasks;
	unsigned m_taskCount;
	std::mutex m_mut;
};

#endif /* TASKPLANNER_H_ */
