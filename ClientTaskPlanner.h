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
	struct ThreadData
	{
		ThreadData( ClientTaskPlanner &Parent );
		//~TaskThrd();

		ThreadPtr m_thread;
		TaskPtr m_task;
		bool m_done;
		ClientTaskPlanner *m_parent;
	};
	typedef std::shared_ptr<ThreadData> ThreadDataPtr;
	typedef std::vector<ThreadDataPtr> ThreadDataPtrs;

	static void ThreadMain( ClientTaskPlanner &parent );
	static void ThreadTask( ThreadData *data );
	void MainSequence();
	void TaskProcess( TaskPtr &task );
	void SendTaskMessage( const unsigned long time, TaskPtr &task );

	bool m_run;
	const unsigned m_threadNums;
	ThreadPtr m_mainThread;
	ThreadDataPtrs m_threads;
	std::mutex m_mut;
	Tasks m_tasks;
	ClientMessageProcessorInterface &m_processor;
};

#endif /* CLIENTTASKPLANNER_H_ */
