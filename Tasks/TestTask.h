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
	TestTask( const unsigned Start, const unsigned End, const unsigned Hash, const unsigned plannerId );
	virtual ~TestTask();

	const static unsigned ID = 1;

	virtual void Process();
	virtual unsigned GetID() const;
	virtual Task* Clone();
	virtual bool isDone();

	virtual Tasks SeperateTask( const unsigned threadNums, const unsigned plannerID ) const;

	unsigned start, end, hash;
	unsigned result;

protected:
	virtual void _SerializeRequest( tinyxml2::XMLDocument &doc ) const;
	virtual void _DeserializeRequest( const tinyxml2::XMLDocument &doc ) ;

	virtual void _SerializeRespond( tinyxml2::XMLDocument &doc ) const;
	virtual void _DeserializeRespond( const tinyxml2::XMLDocument &doc ) ;
};

#endif /* TESTTASK_H_ */
