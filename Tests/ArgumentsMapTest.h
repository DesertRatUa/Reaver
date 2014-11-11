#ifndef ARGUMENTSMAPTEST_H_
#define ARGUMENTSMAPTEST_H_

#include <cxxtest/TestSuite.h>

#define private public
#include "ArgumentsMap.h"

class ArgumentsMapTest : public CxxTest::TestSuite
{
public:
	void testExceptions()
	{
		ArgumentsMap map;
		TS_ASSERT_THROWS_ANYTHING( map.Get("FirstArg") );
		TS_ASSERT_THROWS_ANYTHING( map.GetShort("frst") );
	}

	void testAdd()
	{
		ArgumentsMap map;
		map.AddArgument( "FirstArg", "frst", "SET!", "First agrument descr" );
		TS_ASSERT_THROWS_NOTHING( map.Get("FirstArg") );
		TS_ASSERT_THROWS_NOTHING( map.GetShort("frst") );
	}

	void testDefaultSet()
	{
		ArgumentsMap map;
		map.AddArgument( "FirstArg", "frst", "SET!", "First agrument descr" );
		TS_ASSERT_EQUALS( map.Get("FirstArg").isSet(), false );
		map.Get("FirstArg").Set();
		TS_ASSERT_EQUALS( map.Get("FirstArg").isSet(), true );
		map.Get("FirstArg").UnSet();
		TS_ASSERT_EQUALS( map.Get("FirstArg").isSet(), false );
	}

	void testSet()
	{
		ArgumentsMap map;
		map.AddArgument( "FirstArg", "frst", "SET!", "First agrument descr" );
		map.Get("FirstArg").Set( "TEST" );
		TS_ASSERT_EQUALS( map.Get("FirstArg").m_value, "TEST" );
	}
};

#endif /*ARGUMENTSMAPTEST_H_*/
