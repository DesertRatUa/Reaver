/*
 * ClientTaskPlanner.h
 *
 *  Created on: 10 но€б. 2014 г.
 *      Author: maximm
 */

#ifndef CLIENTTASKPLANNER_H_
#define CLIENTTASKPLANNER_H_

#include "include.h"
#include "Tasks/Task.h"
#include "Thread.h"

class ClientTaskPlanner
{
public:
	ClientTaskPlanner( unsigned ThreadNums );
	virtual ~ClientTaskPlanner();

	void Init();
	void Run();
	void Stop();

	void AddTask( TaskPtr &task );

protected:
	struct TaskThrd
	{
		TaskThrd();
		ThreadPtr thread;
		bool Done;
	};
	typedef std::vector<TaskThrd> TaskThrds;

	static void Thread( ClientTaskPlanner &parent );
	static void TaskThread( TaskPtr task, TaskThrd &thread );
	void TaskPlanner();

	bool m_run;
	unsigned m_threadNums;
	ThreadPtr m_mainThread;
	TaskThrds m_threads;
	std::mutex m_mut;
	Tasks m_tasks;
};

#endif /* CLIENTTASKPLANNER_H_ */
