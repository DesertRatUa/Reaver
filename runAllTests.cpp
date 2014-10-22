/* Generated file, do not edit */



#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH

#define CXXTEST_TRAP_SIGNALS
#define _CXXTEST_ABORT_TEST_ON_FAIL

#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ListenerList.h>
#include <cxxtest/XmlStdioPrinter.h>


typedef const CxxTest::SuiteDescription *SuiteDescriptionPtr;
typedef const CxxTest::TestDescription *TestDescriptionPtr;

// BEGIN: Test world (declarations of all test suites)

// Test suite: ArgumentsMapTest

#include "ArgumentsMapTest.h"
static ArgumentsMapTest *suite_ArgumentsMapTest;
static CxxTest::List Tests_ArgumentsMapTest;

CxxTest::StaticSuiteDescription suiteDescription_ArgumentsMapTest;


static class TestDescription_ArgumentsMapTest_testExceptions : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_ArgumentsMapTest) suite_ArgumentsMapTest->testExceptions(); }
} testDescription_ArgumentsMapTest_testExceptions;
static class TestDescription_ArgumentsMapTest_testAdd : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_ArgumentsMapTest) suite_ArgumentsMapTest->testAdd(); }
} testDescription_ArgumentsMapTest_testAdd;
static class TestDescription_ArgumentsMapTest_testDefaultSet : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_ArgumentsMapTest) suite_ArgumentsMapTest->testDefaultSet(); }
} testDescription_ArgumentsMapTest_testDefaultSet;
static class TestDescription_ArgumentsMapTest_testSet : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_ArgumentsMapTest) suite_ArgumentsMapTest->testSet(); }
} testDescription_ArgumentsMapTest_testSet;

// Test suite: ServerCommunicationManagerTest

#include "ServerCommunicationManagerTest.h"
static ServerCommunicationManagerTest *suite_ServerCommunicationManagerTest;
static CxxTest::List Tests_ServerCommunicationManagerTest;

CxxTest::StaticSuiteDescription suiteDescription_ServerCommunicationManagerTest;


static class TestDescription_ServerCommunicationManagerTest_testRegisterClient : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_ServerCommunicationManagerTest) suite_ServerCommunicationManagerTest->testRegisterClient(); }
} testDescription_ServerCommunicationManagerTest_testRegisterClient;



// END: Test world

namespace CxxTest
{
	void initialize()
	{
		// Initialize test suite: ArgumentsMapTest
		Tests_ArgumentsMapTest.initialize();

		_TS_TRY_WITH_SIGNAL_PROTECTION {
			_TS_TRY { suite_ArgumentsMapTest = new ArgumentsMapTest; } _TS_PROPAGATE_SIGNAL _TS_CATCH_ABORT( {} )
			_TS_LAST_CATCH( { CxxTest::__cxxtest_failed_init_suites.addSuite("ArgumentsMapTest", "Exception thrown when initializing " "ArgumentsMapTest"); } )
		} _TS_CATCH_SIGNAL( { CxxTest::__cxxtest_failed_init_suites.addSuite("ArgumentsMapTest", CxxTest::__cxxtest_sigmsg.c_str()); } );

		suiteDescription_ArgumentsMapTest.initialize(
			"ArgumentsMapTest.h", 9,
			"ArgumentsMapTest", *suite_ArgumentsMapTest, Tests_ArgumentsMapTest);
		testDescription_ArgumentsMapTest_testExceptions.initialize(Tests_ArgumentsMapTest, suiteDescription_ArgumentsMapTest, 12, "testExceptions");
		testDescription_ArgumentsMapTest_testAdd.initialize(Tests_ArgumentsMapTest, suiteDescription_ArgumentsMapTest, 19, "testAdd");
		testDescription_ArgumentsMapTest_testDefaultSet.initialize(Tests_ArgumentsMapTest, suiteDescription_ArgumentsMapTest, 27, "testDefaultSet");
		testDescription_ArgumentsMapTest_testSet.initialize(Tests_ArgumentsMapTest, suiteDescription_ArgumentsMapTest, 38, "testSet");

		// Initialize test suite: ServerCommunicationManagerTest
		Tests_ServerCommunicationManagerTest.initialize();

		_TS_TRY_WITH_SIGNAL_PROTECTION {
			_TS_TRY { suite_ServerCommunicationManagerTest = new ServerCommunicationManagerTest; } _TS_PROPAGATE_SIGNAL _TS_CATCH_ABORT( {} )
			_TS_LAST_CATCH( { CxxTest::__cxxtest_failed_init_suites.addSuite("ServerCommunicationManagerTest", "Exception thrown when initializing " "ServerCommunicationManagerTest"); } )
		} _TS_CATCH_SIGNAL( { CxxTest::__cxxtest_failed_init_suites.addSuite("ServerCommunicationManagerTest", CxxTest::__cxxtest_sigmsg.c_str()); } );

		suiteDescription_ServerCommunicationManagerTest.initialize(
			"ServerCommunicationManagerTest.h", 8,
			"ServerCommunicationManagerTest", *suite_ServerCommunicationManagerTest, Tests_ServerCommunicationManagerTest);
		testDescription_ServerCommunicationManagerTest_testRegisterClient.initialize(Tests_ServerCommunicationManagerTest, suiteDescription_ServerCommunicationManagerTest, 11, "testRegisterClient");


	}
	
	void cleanup()
	{
		delete suite_ArgumentsMapTest;
		delete suite_ServerCommunicationManagerTest;

	}
}

#include <cxxtest/Root.cpp>


#include <dereferee-src/allocation_info_impl.cpp>
#include <dereferee-src/cxxtest_listener.cpp>
#include <dereferee-src/manager.cpp>
#include <dereferee-src/memtab.cpp>
#include <dereferee-src/usage_stats_impl.cpp>
#include <dereferee-src/gcc_nodebug_platform.cpp>

class CxxTestMain
{
public:
	CxxTestMain()
	{
CxxTest::initialize();

		CxxTest::ListenerList listeners;
		CxxTest::XmlStdioPrinter listener_1; listeners.addListener(listener_1);

		CxxTest::TestRunner::runAllTests(listeners);
		CxxTest::__cxxtest_runCompleted = true;
		CxxTest::cleanup();
	}
};

CxxTestMain cxxTestMain;



