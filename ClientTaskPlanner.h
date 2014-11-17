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

class ClientMessageProcessorInterface;

class ClientTaskPlanner
{
public:
	ClientTaskPlanner( ClientMessageProcessorInterface &processor, unsigned ThreadNums );
	virtual ~ClientTaskPlanner();

	void Init();
	void Run();
	void Stop();

	void AddTask( TaskPtr &task );

protected:
	struct TaskThrd
	{
		TaskThrd( ClientTaskPlanner &Parent );
		ThreadPtr thread;
		TaskPtr task;
		bool Done;
		ClientTaskPlanner *parent;
	};
	typedef std::vector<TaskThrd> TaskThrds;

	static void ThreadMain( ClientTaskPlanner &parent );
	static void ThreadTask( TaskThrd *thread );
	void MainSequence();
	void TaskProcess( TaskPtr &task );

	bool m_run;
	unsigned m_threadNums;
	ThreadPtr m_mainThread;
	TaskThrds m_threads;
	std::mutex m_mut;
	Tasks m_tasks;
	ClientMessageProcessorInterface &m_processor;
};

#endif /* CLIENTTASKPLANNER_H_ */
