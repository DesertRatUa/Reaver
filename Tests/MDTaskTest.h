#ifndef MDTASKTEST_H_
#define MDTASKTEST_H_

#include <cxxtest/TestSuite.h>

#define protected public
#include "Tasks\MD5Task.h"
#undef protected

class MDTaskTest : public CxxTest::TestSuite
{
public:
	void testGetMD5()
	{
		std::string text = "123456";
		//Log::Add( "MD5: " + MD5Task::GetMD5( text ) );
		MD5Task task;
		TS_ASSERT_EQUALS( task.GetMD5( text ), "e10adc3949ba59abbe56e057f20f883e" );
	}

	void testProcessing()
	{
		MD5Task task;
		task.Hash = "c20ad4d76fe97759aa27a0c99bff6710";
		task.begin = 1;
		task.end = 15;
		task.Process();
		//Log::Add( "MD5 Task " + Log::IntToStr(  task.result ) );
		TS_ASSERT_EQUALS( task.result, unsigned( 12 ) );
	}
};

#endif /*MDTASKTEST_H_*/
