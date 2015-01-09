#ifndef REQUESTTASKTEST_H_
#define REQUESTTASKTEST_H_

#include <cxxtest/TestSuite.h>

#include "Messages/RequestTaskMessage.h"

class RequestTaskTest : public CxxTest::TestSuite
{
public:
	void testRequest()
	{
        RequestTaskMessage mess(2);
        std::string xml = mess.SerializeReqestStr();

        RequestTaskMessage mess1;
        mess1.DeserializeReqestStr( xml );

        TS_ASSERT_EQUALS( mess.m_threads, mess1.m_threads );
	}
};

#endif /*REQUESTTASKTEST_H_*/
