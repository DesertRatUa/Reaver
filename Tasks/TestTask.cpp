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

TestTask::TestTask( const unsigned Start, const unsigned End, const unsigned Hash ) : start( Start ), end( End ), hash( Hash ), result(0)
{
}

TestTask::~TestTask()
{
}

void TestTask::SerializeRequest( tinyxml2::XMLDocument &doc ) const
{
	XMLUtils::AddUnsigned( doc, "Start", start );
	XMLUtils::AddUnsigned( doc, "End", end );
	XMLUtils::AddUnsigned( doc, "Hash", hash );
}

void TestTask::DeserializeRequest( const tinyxml2::XMLDocument &doc )
{
	XMLUtils::GetUnsigned( doc, "Start", start );
	XMLUtils::GetUnsigned( doc, "End", end );
	XMLUtils::GetUnsigned( doc, "Hash", hash );
}

void TestTask::SerializeRespond( tinyxml2::XMLDocument &doc ) const
{
	XMLUtils::AddUnsigned( doc, "Result", result );
}

void TestTask::DeserializeRespond( const tinyxml2::XMLDocument &doc )
{
	XMLUtils::GetUnsigned( doc, "Result", result );
}

void TestTask::Process()
{
	for( unsigned i = start; i < end; ++i )
	{
		if ( (i + 5)*35 == hash )
		{
			result = i;
			return;
		}
	}
	Sleep(3000);
}

unsigned TestTask::GetID() const
{
	return ID;
}
