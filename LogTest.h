#ifndef LOGTEST_H_
#define LOGTEST_H_

#include <cxxtest/TestSuite.h>

#include "Log.h"

class LogTest : public CxxTest::TestSuite
{
public:
	void testInit()
	{
		TS_ASSERT_THROWS_ANYTHING( Log::Init( "C:\\Tmp_NoExist\\" ) );
		TS_ASSERT_THROWS_NOTHING( Log::Init( "C:\\Windows\\Temp\\" ) );
		std::fstream file( "C:\\Windows\\Temp\\Log.log", std::ios::in );
		TS_ASSERT_EQUALS( file.is_open(), true );
		file.close();
		Log::Close();
	}

	void testAddrToStr()
	{
		sockaddr_in addr;
		addr.sin_addr.s_addr = inet_addr( "127.0.0.1" );
		addr.sin_port = 89;
		TS_ASSERT_EQUALS( Log::AddrToStr( addr ), "127.0.0.1:89" );
	}

	void testIntToStr()
	{
		TS_ASSERT_EQUALS( Log::IntToStr( 123 ), "123" );
	}
};

#endif /*LOGTEST_H_*/
