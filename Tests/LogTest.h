#ifndef LOGTEST_H_
#define LOGTEST_H_

#include <cxxtest/TestSuite.h>

#include "Log.h"
#include "winsock2.h"

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
		addr.sin_port = htons( 89 );
		TS_ASSERT_EQUALS( Log::AddrToStr( addr ), "127.0.0.1:89" );
	}

	void testStrToAddr()
	{
		std::string addr( "127.0.0.1:80" );
		sockaddr_in res = Log::StrToAddr( addr );
		TS_ASSERT_EQUALS( ntohs( res.sin_port ),  80 );
		TS_ASSERT_EQUALS( std::string( inet_ntoa( res.sin_addr ) ), std::string( "127.0.0.1" ) );
	}

	void testIntToStr()
	{
		TS_ASSERT_EQUALS( Log::IntToStr( 123 ), "123" );
	}

	void testBoolToStr()
	{
		TS_ASSERT_EQUALS( Log::BoolToStr( true ), "true" );
		TS_ASSERT_EQUALS( Log::BoolToStr( false ), "false" );
	}

	void testStrToBool()
	{
		bool value = false;
		Log::StrToBool( "Tru", value );
		TS_ASSERT_EQUALS( value, false );
		Log::StrToBool( "TRUE", value );
		TS_ASSERT_EQUALS( value, true );
		value = false;
		Log::StrToBool( "true", value );
		TS_ASSERT_EQUALS( value, true );
		Log::StrToBool( "False", value );
		TS_ASSERT_EQUALS( value, false );
	}
};
#endif /*LOGTEST_H_*/
