/*
 * TaskPlanner.h
 *
 *  Created on: 03 но€б. 2014 г.
 *      Author: maximm
 */

#ifndef TASKPLANNER_H_
#define TASKPLANNER_H_

class TaskPlanner
{
public:
	TaskPlanner();
	virtual ~TaskPlanner();

	void Init();
	void Run();
	void AddTask( TaskPtr &task );

protected:
	typedef std::vector<TaskPtr> Tasks;
	Tasks m_tasks;
};

#endif /* TASKPLANNER_H_ */
