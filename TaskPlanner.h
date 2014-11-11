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

class NodesMap;

class TaskPlanner
{
public:
	TaskPlanner( NodesMap &map );
	virtual ~TaskPlanner();

	void Init();
	void Run();
	void Stop();
	void AddTask( const TaskPtr &task, const unsigned threadsNum );
	void TaskComplete( const TaskPtr &task );

protected:
	static void Thread( TaskPlanner &parent );
	void ThreadRun();

	Tasks m_tasks;
	NodesMap &m_nodes;
	unsigned m_taskCount;
	bool m_run;
	std::mutex m_mut;
	ThreadPtr m_thread;
};

#endif /* TASKPLANNER_H_ */
