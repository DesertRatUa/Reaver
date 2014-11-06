/*
 * TestTask.h
 *
 *  Created on: 09 сент. 2014 г.
 *      Author: maximm
 */

#ifndef TESTTASK_H_
#define TESTTASK_H_

#include "include.h"
#include "Tasks/Task.h"

class TestTask: public Task
{
public:
	TestTask();
	TestTask( const unsigned Start, const unsigned End, const unsigned Hash );
	virtual ~TestTask();

	const static unsigned ID = 1;

	virtual void SerializeRequest( tinyxml2::XMLDocument &doc ) const;
	virtual void DeserializeRequest( const tinyxml2::XMLDocument &doc ) ;

	virtual void SerializeRespond( tinyxml2::XMLDocument &doc ) const;
	virtual void DeserializeRespond( const tinyxml2::XMLDocument &doc ) ;

	virtual void Process();
	virtual unsigned GetID() const;

	virtual Tasks SeperateTask( const unsigned threadNums, const unsigned plannerID ) const;

	unsigned start, end, hash;
	unsigned result;

protected:

};

#endif /* TESTTASK_H_ */
