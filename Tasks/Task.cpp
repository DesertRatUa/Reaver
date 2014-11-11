/*
 * Task.cpp
 *
 *  Created on: 08 сент. 2014 г.
 *      Author: maximm
 */

#include "Tasks/Task.h"
#include "TestTask.h"
#include "tinyxml2.h"
using namespace tinyxml2;

Task::Task() : m_plannerID(0)
{
}

Task::Task( const unsigned plannerId ): m_plannerID(plannerId)
{

}

Task::~Task()
{
}

Task* Task::CreateTask( const unsigned id )
{
	switch ( id )
	{
		case 1 : return new TestTask();
		default : return NULL;
	}
}

void Task::ReSerializeRequest()
{
	XMLDocument doc;
	XMLPrinter printer;
	SerializeRequest( doc );
	doc.Print( &printer );
	doc.Clear();
	doc.Parse( printer.CStr(), printer.CStrSize() );
	DeserializeRequest( doc );
}

void Task::ReSerializeRespond()
{
	XMLDocument doc;
	XMLPrinter printer;
	SerializeRespond( doc );
	doc.Print( &printer );
	doc.Clear();
	doc.Parse( printer.CStr(), printer.CStrSize() );
	DeserializeRespond( doc );
}

unsigned Task::GetPlannerID()
{
	return m_plannerID;
}
