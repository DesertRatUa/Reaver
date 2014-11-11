/*
 * TestTask.cpp
 *
 *  Created on: 09 сент. 2014 г.
 *      Author: maximm
 */

#include <Tasks/TestTask.h>
#include "XMLUtils.h"
#include <windows.h>
#include "Log.h"

TestTask::TestTask() : start(0), end(0), hash(0), result(0)
{
}

TestTask::TestTask( const unsigned Start, const unsigned End, const unsigned Hash ) :
		start( Start ), end( End ), hash( Hash ), result(0)
{
}

TestTask::TestTask( const unsigned Start, const unsigned End, const unsigned Hash, const unsigned plannerId ) :
		start( Start ), end( End ), hash( Hash ), result(0) , Task( plannerId )
{
}

TestTask::~TestTask()
{
}

void TestTask::SerializeRequest( tinyxml2::XMLDocument &doc ) const
{
	XMLUtils::AddInt( doc, "Start", start );
	XMLUtils::AddInt( doc, "End", end );
	XMLUtils::AddInt( doc, "Hash", hash );
}

void TestTask::DeserializeRequest( const tinyxml2::XMLDocument &doc )
{
	XMLUtils::GetInt( doc, "Start", start );
	XMLUtils::GetInt( doc, "End", end );
	XMLUtils::GetInt( doc, "Hash", hash );
}

void TestTask::SerializeRespond( tinyxml2::XMLDocument &doc ) const
{
	XMLUtils::AddInt( doc, "Result", result );
}

void TestTask::DeserializeRespond( const tinyxml2::XMLDocument &doc )
{
	XMLUtils::GetInt( doc, "Result", result );
}

void TestTask::Process()
{
	for( unsigned i = start; i < end; ++i )
	{
		if (  i == hash )
		{
			result = i;
			return;
		}
		Sleep(100);
	}
}

unsigned TestTask::GetID() const
{
	return ID;
}

Tasks TestTask::SeperateTask( const unsigned threadNums, const unsigned plannerID ) const
{
	Tasks tasks;
	if ( threadNums < 2 )
	{
		tasks.push_back( TaskPtr( new TestTask( *this ) ) );
		return tasks;
	}
	unsigned st = start;
	unsigned step = ( end - start ) / threadNums;
	for ( unsigned i = 0; i < threadNums; ++i )
	{
		tasks.push_back( TaskPtr( new TestTask( st, st+=step, hash, plannerID ) ) );
	}
	return tasks;
}
