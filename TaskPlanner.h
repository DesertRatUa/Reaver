/*
 * TaskPlanner.h
 *
 *  Created on: 03 но€б. 2014 г.
 *      Author: maximm
 */

#ifndef TASKPLANNER_H_
#define TASKPLANNER_H_

#include "Tasks/Task.h"
#include "include.h"
#include "vector"
#include "mutex"

class TaskPlanner
{
public:
	TaskPlanner();
	virtual ~TaskPlanner();

	void Init();
	void Run();
	void AddTask( const TaskPtr &task, const unsigned threadsNum );
	void TaskComplete( const TaskPtr &task );

protected:

	Tasks m_tasks;
	unsigned m_taskCount;
	std::mutex m_mut;
};

#endif /* TASKPLANNER_H_ */
