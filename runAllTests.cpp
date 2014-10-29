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

// Test suite: ClientsMapTest

#include "ClientsMapTest.h"
static ClientsMapTest *suite_ClientsMapTest;
static CxxTest::List Tests_ClientsMapTest;

CxxTest::StaticSuiteDescription suiteDescription_ClientsMapTest;


static class TestDescription_ClientsMapTest_testRegister : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_ClientsMapTest) suite_ClientsMapTest->testRegister(); }
} testDescription_ClientsMapTest_testRegister;
static class TestDescription_ClientsMapTest_testUnregister : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_ClientsMapTest) suite_ClientsMapTest->testUnregister(); }
} testDescription_ClientsMapTest_testUnregister;
static class TestDescription_ClientsMapTest_testRemoveDisconnected : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_ClientsMapTest) suite_ClientsMapTest->testRemoveDisconnected(); }
} testDescription_ClientsMapTest_testRemoveDisconnected;

// Test suite: LogTest

#include "LogTest.h"
static LogTest *suite_LogTest;
static CxxTest::List Tests_LogTest;

CxxTest::StaticSuiteDescription suiteDescription_LogTest;


static class TestDescription_LogTest_testInit : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_LogTest) suite_LogTest->testInit(); }
} testDescription_LogTest_testInit;
static class TestDescription_LogTest_testAddrToStr : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_LogTest) suite_LogTest->testAddrToStr(); }
} testDescription_LogTest_testAddrToStr;
static class TestDescription_LogTest_testIntToStr : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_LogTest) suite_LogTest->testIntToStr(); }
} testDescription_LogTest_testIntToStr;

// Test suite: MessageProcessorTest

#include "MessageProcessorTest.h"
static MessageProcessorTest *suite_MessageProcessorTest;
static CxxTest::List Tests_MessageProcessorTest;

CxxTest::StaticSuiteDescription suiteDescription_MessageProcessorTest;


static class TestDescription_MessageProcessorTest_testRegisterProcessor : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_MessageProcessorTest) suite_MessageProcessorTest->testRegisterProcessor(); }
} testDescription_MessageProcessorTest_testRegisterProcessor;
static class TestDescription_MessageProcessorTest_testProcessMessage : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_MessageProcessorTest) suite_MessageProcessorTest->testProcessMessage(); }
} testDescription_MessageProcessorTest_testProcessMessage;

// Test suite: XMLUtilsTest

#include "XMLUtilsTest.h"
static XMLUtilsTest *suite_XMLUtilsTest;
static CxxTest::List Tests_XMLUtilsTest;

CxxTest::StaticSuiteDescription suiteDescription_XMLUtilsTest;


static class TestDescription_XMLUtilsTest_testAddPacketID : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_XMLUtilsTest) suite_XMLUtilsTest->testAddPacketID(); }
} testDescription_XMLUtilsTest_testAddPacketID;
static class TestDescription_XMLUtilsTest_testAddText : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_XMLUtilsTest) suite_XMLUtilsTest->testAddText(); }
} testDescription_XMLUtilsTest_testAddText;
static class TestDescription_XMLUtilsTest_testAddInt : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_XMLUtilsTest) suite_XMLUtilsTest->testAddInt(); }
} testDescription_XMLUtilsTest_testAddInt;
static class TestDescription_XMLUtilsTest_testGetText : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_XMLUtilsTest) suite_XMLUtilsTest->testGetText(); }
} testDescription_XMLUtilsTest_testGetText;
static class TestDescription_XMLUtilsTest_testGetInt : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_XMLUtilsTest) suite_XMLUtilsTest->testGetInt(); }
} testDescription_XMLUtilsTest_testGetInt;
static class TestDescription_XMLUtilsTest_testGetPacketId : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_XMLUtilsTest) suite_XMLUtilsTest->testGetPacketId(); }
} testDescription_XMLUtilsTest_testGetPacketId;
static class TestDescription_XMLUtilsTest_testPacketId : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_XMLUtilsTest) suite_XMLUtilsTest->testPacketId(); }
} testDescription_XMLUtilsTest_testPacketId;



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

		// Initialize test suite: ClientsMapTest
		Tests_ClientsMapTest.initialize();

		_TS_TRY_WITH_SIGNAL_PROTECTION {
			_TS_TRY { suite_ClientsMapTest = new ClientsMapTest; } _TS_PROPAGATE_SIGNAL _TS_CATCH_ABORT( {} )
			_TS_LAST_CATCH( { CxxTest::__cxxtest_failed_init_suites.addSuite("ClientsMapTest", "Exception thrown when initializing " "ClientsMapTest"); } )
		} _TS_CATCH_SIGNAL( { CxxTest::__cxxtest_failed_init_suites.addSuite("ClientsMapTest", CxxTest::__cxxtest_sigmsg.c_str()); } );

		suiteDescription_ClientsMapTest.initialize(
			"ClientsMapTest.h", 8,
			"ClientsMapTest", *suite_ClientsMapTest, Tests_ClientsMapTest);
		testDescription_ClientsMapTest_testRegister.initialize(Tests_ClientsMapTest, suiteDescription_ClientsMapTest, 11, "testRegister");
		testDescription_ClientsMapTest_testUnregister.initialize(Tests_ClientsMapTest, suiteDescription_ClientsMapTest, 27, "testUnregister");
		testDescription_ClientsMapTest_testRemoveDisconnected.initialize(Tests_ClientsMapTest, suiteDescription_ClientsMapTest, 41, "testRemoveDisconnected");

		// Initialize test suite: LogTest
		Tests_LogTest.initialize();

		_TS_TRY_WITH_SIGNAL_PROTECTION {
			_TS_TRY { suite_LogTest = new LogTest; } _TS_PROPAGATE_SIGNAL _TS_CATCH_ABORT( {} )
			_TS_LAST_CATCH( { CxxTest::__cxxtest_failed_init_suites.addSuite("LogTest", "Exception thrown when initializing " "LogTest"); } )
		} _TS_CATCH_SIGNAL( { CxxTest::__cxxtest_failed_init_suites.addSuite("LogTest", CxxTest::__cxxtest_sigmsg.c_str()); } );

		suiteDescription_LogTest.initialize(
			"LogTest.h", 8,
			"LogTest", *suite_LogTest, Tests_LogTest);
		testDescription_LogTest_testInit.initialize(Tests_LogTest, suiteDescription_LogTest, 11, "testInit");
		testDescription_LogTest_testAddrToStr.initialize(Tests_LogTest, suiteDescription_LogTest, 21, "testAddrToStr");
		testDescription_LogTest_testIntToStr.initialize(Tests_LogTest, suiteDescription_LogTest, 29, "testIntToStr");

		// Initialize test suite: MessageProcessorTest
		Tests_MessageProcessorTest.initialize();

		_TS_TRY_WITH_SIGNAL_PROTECTION {
			_TS_TRY { suite_MessageProcessorTest = new MessageProcessorTest; } _TS_PROPAGATE_SIGNAL _TS_CATCH_ABORT( {} )
			_TS_LAST_CATCH( { CxxTest::__cxxtest_failed_init_suites.addSuite("MessageProcessorTest", "Exception thrown when initializing " "MessageProcessorTest"); } )
		} _TS_CATCH_SIGNAL( { CxxTest::__cxxtest_failed_init_suites.addSuite("MessageProcessorTest", CxxTest::__cxxtest_sigmsg.c_str()); } );

		suiteDescription_MessageProcessorTest.initialize(
			"MessageProcessorTest.h", 10,
			"MessageProcessorTest", *suite_MessageProcessorTest, Tests_MessageProcessorTest);
		testDescription_MessageProcessorTest_testRegisterProcessor.initialize(Tests_MessageProcessorTest, suiteDescription_MessageProcessorTest, 29, "testRegisterProcessor");
		testDescription_MessageProcessorTest_testProcessMessage.initialize(Tests_MessageProcessorTest, suiteDescription_MessageProcessorTest, 37, "testProcessMessage");

		// Initialize test suite: XMLUtilsTest
		Tests_XMLUtilsTest.initialize();

		_TS_TRY_WITH_SIGNAL_PROTECTION {
			_TS_TRY { suite_XMLUtilsTest = new XMLUtilsTest; } _TS_PROPAGATE_SIGNAL _TS_CATCH_ABORT( {} )
			_TS_LAST_CATCH( { CxxTest::__cxxtest_failed_init_suites.addSuite("XMLUtilsTest", "Exception thrown when initializing " "XMLUtilsTest"); } )
		} _TS_CATCH_SIGNAL( { CxxTest::__cxxtest_failed_init_suites.addSuite("XMLUtilsTest", CxxTest::__cxxtest_sigmsg.c_str()); } );

		suiteDescription_XMLUtilsTest.initialize(
			"XMLUtilsTest.h", 8,
			"XMLUtilsTest", *suite_XMLUtilsTest, Tests_XMLUtilsTest);
		testDescription_XMLUtilsTest_testAddPacketID.initialize(Tests_XMLUtilsTest, suiteDescription_XMLUtilsTest, 11, "testAddPacketID");
		testDescription_XMLUtilsTest_testAddText.initialize(Tests_XMLUtilsTest, suiteDescription_XMLUtilsTest, 20, "testAddText");
		testDescription_XMLUtilsTest_testAddInt.initialize(Tests_XMLUtilsTest, suiteDescription_XMLUtilsTest, 29, "testAddInt");
		testDescription_XMLUtilsTest_testGetText.initialize(Tests_XMLUtilsTest, suiteDescription_XMLUtilsTest, 38, "testGetText");
		testDescription_XMLUtilsTest_testGetInt.initialize(Tests_XMLUtilsTest, suiteDescription_XMLUtilsTest, 47, "testGetInt");
		testDescription_XMLUtilsTest_testGetPacketId.initialize(Tests_XMLUtilsTest, suiteDescription_XMLUtilsTest, 57, "testGetPacketId");
		testDescription_XMLUtilsTest_testPacketId.initialize(Tests_XMLUtilsTest, suiteDescription_XMLUtilsTest, 67, "testPacketId");


	}
	
	void cleanup()
	{
		delete suite_ArgumentsMapTest;
		delete suite_ClientsMapTest;
		delete suite_LogTest;
		delete suite_MessageProcessorTest;
		delete suite_XMLUtilsTest;

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



