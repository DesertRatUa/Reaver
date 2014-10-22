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

class Task
{
public:
	Task();
	virtual ~Task();

	virtual void SerializeRequest( tinyxml2::XMLDocument &doc ) const = 0;
	virtual void DeserializeRequest( const tinyxml2::XMLDocument &doc )  = 0;

	virtual void SerializeRespond( tinyxml2::XMLDocument &doc ) const = 0;
	virtual void DeserializeRespond( const tinyxml2::XMLDocument &doc ) = 0;

	virtual void Process() = 0;
	virtual unsigned GetID() const = 0;

	static Task* CreateTask( const unsigned id );
};

typedef std::shared_ptr<Task> TaskPtr;

#endif /* TASK_H_ */
