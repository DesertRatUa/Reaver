/*
 * Task.h
 *
 *  Created on: 08 сент. 2014 г.
 *      Author: maximm
 */

#ifndef TASK_H_
#define TASK_H_

#include "include.h"
#include <memory>
#include <deque>


class Task
{
public:
	Task();
	Task( const unsigned plannerId );
	virtual ~Task();

	virtual void SerializeRequest( tinyxml2::XMLDocument &doc ) const = 0;
	virtual void DeserializeRequest( const tinyxml2::XMLDocument &doc )  = 0;

	virtual void SerializeRespond( tinyxml2::XMLDocument &doc ) const = 0;
	virtual void DeserializeRespond( const tinyxml2::XMLDocument &doc ) = 0;

	virtual void Process() = 0;
	virtual unsigned GetID() const = 0;

	unsigned GetPlannerID();
	virtual std::deque<std::shared_ptr<Task>> SeperateTask( const unsigned threadNums, const unsigned plannerID ) const = 0;

	static Task* CreateTask( const unsigned id );

	void ReSerializeRequest();
	void ReSerializeRespond();

protected:
	unsigned m_plannerID;
};

typedef std::shared_ptr<Task> TaskPtr;
typedef std::deque<TaskPtr> Tasks;

#endif /* TASK_H_ */
