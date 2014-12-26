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

#include "Tests\ArgumentsMapTest.h"
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

// Test suite: ClientTaskPlannerTest

#include "Tests\ClientTaskPlannerTest.h"
static ClientTaskPlannerTest *suite_ClientTaskPlannerTest;
static CxxTest::List Tests_ClientTaskPlannerTest;

CxxTest::StaticSuiteDescription suiteDescription_ClientTaskPlannerTest;


static class TestDescription_ClientTaskPlannerTest_testAddTask : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_ClientTaskPlannerTest) suite_ClientTaskPlannerTest->testAddTask(); }
} testDescription_ClientTaskPlannerTest_testAddTask;
static class TestDescription_ClientTaskPlannerTest_testRun : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_ClientTaskPlannerTest) suite_ClientTaskPlannerTest->testRun(); }
} testDescription_ClientTaskPlannerTest_testRun;

// Test suite: ClientsMapTest

#include "Tests\ClientsMapTest.h"
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

#include "Tests\LogTest.h"
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
static class TestDescription_LogTest_testStrToAddr : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_LogTest) suite_LogTest->testStrToAddr(); }
} testDescription_LogTest_testStrToAddr;
static class TestDescription_LogTest_testIntToStr : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_LogTest) suite_LogTest->testIntToStr(); }
} testDescription_LogTest_testIntToStr;
static class TestDescription_LogTest_testBoolToStr : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_LogTest) suite_LogTest->testBoolToStr(); }
} testDescription_LogTest_testBoolToStr;
static class TestDescription_LogTest_testStrToBool : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_LogTest) suite_LogTest->testStrToBool(); }
} testDescription_LogTest_testStrToBool;

// Test suite: MDTaskTest

#include "Tests\MDTaskTest.h"
static MDTaskTest *suite_MDTaskTest;
static CxxTest::List Tests_MDTaskTest;

CxxTest::StaticSuiteDescription suiteDescription_MDTaskTest;


static class TestDescription_MDTaskTest_testGetMD5 : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_MDTaskTest) suite_MDTaskTest->testGetMD5(); }
} testDescription_MDTaskTest_testGetMD5;
static class TestDescription_MDTaskTest_testProcessing : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_MDTaskTest) suite_MDTaskTest->testProcessing(); }
} testDescription_MDTaskTest_testProcessing;

// Test suite: MessageProcessorTest

#include "Tests\MessageProcessorTest.h"
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

// Test suite: NodeTest

#include "Tests\NodeTest.h"
static NodeTest *suite_NodeTest;
static CxxTest::List Tests_NodeTest;

CxxTest::StaticSuiteDescription suiteDescription_NodeTest;


static class TestDescription_NodeTest_testSendTask : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_NodeTest) suite_NodeTest->testSendTask(); }
} testDescription_NodeTest_testSendTask;
static class TestDescription_NodeTest_testTaskComplete : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_NodeTest) suite_NodeTest->testTaskComplete(); }
} testDescription_NodeTest_testTaskComplete;
static class TestDescription_NodeTest_testisThreadsAvalible : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_NodeTest) suite_NodeTest->testisThreadsAvalible(); }
} testDescription_NodeTest_testisThreadsAvalible;
static class TestDescription_NodeTest_testGetFreeThreadsNum : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_NodeTest) suite_NodeTest->testGetFreeThreadsNum(); }
} testDescription_NodeTest_testGetFreeThreadsNum;
static class TestDescription_NodeTest_testGetID : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_NodeTest) suite_NodeTest->testGetID(); }
} testDescription_NodeTest_testGetID;
static class TestDescription_NodeTest_testCheckForStaleTasks : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_NodeTest) suite_NodeTest->testCheckForStaleTasks(); }
} testDescription_NodeTest_testCheckForStaleTasks;

// Test suite: NodesMapTest

#include "Tests\NodesMapTest.h"
static NodesMapTest *suite_NodesMapTest;
static CxxTest::List Tests_NodesMapTest;

CxxTest::StaticSuiteDescription suiteDescription_NodesMapTest;


static class TestDescription_NodesMapTest_testRegisterNode : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_NodesMapTest) suite_NodesMapTest->testRegisterNode(); }
} testDescription_NodesMapTest_testRegisterNode;
static class TestDescription_NodesMapTest_testUnregisterNode : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_NodesMapTest) suite_NodesMapTest->testUnregisterNode(); }
} testDescription_NodesMapTest_testUnregisterNode;
static class TestDescription_NodesMapTest_testGetNode : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_NodesMapTest) suite_NodesMapTest->testGetNode(); }
} testDescription_NodesMapTest_testGetNode;
static class TestDescription_NodesMapTest_testGetThreadsNum : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_NodesMapTest) suite_NodesMapTest->testGetThreadsNum(); }
} testDescription_NodesMapTest_testGetThreadsNum;
static class TestDescription_NodesMapTest_testTaskComplete : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_NodesMapTest) suite_NodesMapTest->testTaskComplete(); }
} testDescription_NodesMapTest_testTaskComplete;

// Test suite: RequestTaskTest

#include "Tests\RequestTaskTest.h"
static RequestTaskTest *suite_RequestTaskTest;
static CxxTest::List Tests_RequestTaskTest;

CxxTest::StaticSuiteDescription suiteDescription_RequestTaskTest;


static class TestDescription_RequestTaskTest_testRequest : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_RequestTaskTest) suite_RequestTaskTest->testRequest(); }
} testDescription_RequestTaskTest_testRequest;

// Test suite: ServerTaskPlannerTest

#include "Tests\ServerTaskPlannerTest.h"
static ServerTaskPlannerTest *suite_ServerTaskPlannerTest;
static CxxTest::List Tests_ServerTaskPlannerTest;

CxxTest::StaticSuiteDescription suiteDescription_ServerTaskPlannerTest;


static class TestDescription_ServerTaskPlannerTest_testAddTask : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_ServerTaskPlannerTest) suite_ServerTaskPlannerTest->testAddTask(); }
} testDescription_ServerTaskPlannerTest_testAddTask;
static class TestDescription_ServerTaskPlannerTest_testTaskComplete : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_ServerTaskPlannerTest) suite_ServerTaskPlannerTest->testTaskComplete(); }
} testDescription_ServerTaskPlannerTest_testTaskComplete;
static class TestDescription_ServerTaskPlannerTest_testGetTask : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_ServerTaskPlannerTest) suite_ServerTaskPlannerTest->testGetTask(); }
} testDescription_ServerTaskPlannerTest_testGetTask;

// Test suite: TaskMessageTest

#include "Tests\TaskMessageTest.h"
static TaskMessageTest *suite_TaskMessageTest;
static CxxTest::List Tests_TaskMessageTest;

CxxTest::StaticSuiteDescription suiteDescription_TaskMessageTest;


static class TestDescription_TaskMessageTest_testRequest : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_TaskMessageTest) suite_TaskMessageTest->testRequest(); }
} testDescription_TaskMessageTest_testRequest;
static class TestDescription_TaskMessageTest_testRequestCancel : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_TaskMessageTest) suite_TaskMessageTest->testRequestCancel(); }
} testDescription_TaskMessageTest_testRequestCancel;
static class TestDescription_TaskMessageTest_testRespond : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_TaskMessageTest) suite_TaskMessageTest->testRespond(); }
} testDescription_TaskMessageTest_testRespond;
static class TestDescription_TaskMessageTest_testRespondCancel : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_TaskMessageTest) suite_TaskMessageTest->testRespondCancel(); }
} testDescription_TaskMessageTest_testRespondCancel;

// Test suite: TaskPlannerTest

#include "Tests\TaskPlannerTest.h"
static TaskPlannerTest *suite_TaskPlannerTest;
static CxxTest::List Tests_TaskPlannerTest;

CxxTest::StaticSuiteDescription suiteDescription_TaskPlannerTest;


static class TestDescription_TaskPlannerTest_testAddTask : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_TaskPlannerTest) suite_TaskPlannerTest->testAddTask(); }
} testDescription_TaskPlannerTest_testAddTask;
static class TestDescription_TaskPlannerTest_testTaskComplete : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_TaskPlannerTest) suite_TaskPlannerTest->testTaskComplete(); }
} testDescription_TaskPlannerTest_testTaskComplete;

// Test suite: UnitTestTask

#include "Tests\TestTask.h"
static UnitTestTask *suite_UnitTestTask;
static CxxTest::List Tests_UnitTestTask;

CxxTest::StaticSuiteDescription suiteDescription_UnitTestTask;


static class TestDescription_UnitTestTask_testRequest : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_UnitTestTask) suite_UnitTestTask->testRequest(); }
} testDescription_UnitTestTask_testRequest;
static class TestDescription_UnitTestTask_testRespond : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_UnitTestTask) suite_UnitTestTask->testRespond(); }
} testDescription_UnitTestTask_testRespond;
static class TestDescription_UnitTestTask_testPlannerID : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_UnitTestTask) suite_UnitTestTask->testPlannerID(); }
} testDescription_UnitTestTask_testPlannerID;

// Test suite: TestTaskTest

#include "Tests\TestTaskTest.h"
static TestTaskTest *suite_TestTaskTest;
static CxxTest::List Tests_TestTaskTest;

CxxTest::StaticSuiteDescription suiteDescription_TestTaskTest;


static class TestDescription_TestTaskTest_testProcess : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_TestTaskTest) suite_TestTaskTest->testProcess(); }
} testDescription_TestTaskTest_testProcess;
static class TestDescription_TestTaskTest_testSeperateTask : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_TestTaskTest) suite_TestTaskTest->testSeperateTask(); }
} testDescription_TestTaskTest_testSeperateTask;

// Test suite: TinyXmlTest

#include "Tests\TinyXmlTest.h"
static TinyXmlTest *suite_TinyXmlTest;
static CxxTest::List Tests_TinyXmlTest;

CxxTest::StaticSuiteDescription suiteDescription_TinyXmlTest;


static class TestDescription_TinyXmlTest_testTinyXML : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_TinyXmlTest) suite_TinyXmlTest->testTinyXML(); }
} testDescription_TinyXmlTest_testTinyXML;

// Test suite: XMLUtilsTest

#include "Tests\XMLUtilsTest.h"
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
static class TestDescription_XMLUtilsTest_testBool : public CxxTest::RealTestDescription {
public:
	void runTest() { if(suite_XMLUtilsTest) suite_XMLUtilsTest->testBool(); }
} testDescription_XMLUtilsTest_testBool;



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
			"Tests\\ArgumentsMapTest.h", 9,
			"ArgumentsMapTest", *suite_ArgumentsMapTest, Tests_ArgumentsMapTest);
		testDescription_ArgumentsMapTest_testExceptions.initialize(Tests_ArgumentsMapTest, suiteDescription_ArgumentsMapTest, 12, "testExceptions");
		testDescription_ArgumentsMapTest_testAdd.initialize(Tests_ArgumentsMapTest, suiteDescription_ArgumentsMapTest, 19, "testAdd");
		testDescription_ArgumentsMapTest_testDefaultSet.initialize(Tests_ArgumentsMapTest, suiteDescription_ArgumentsMapTest, 27, "testDefaultSet");
		testDescription_ArgumentsMapTest_testSet.initialize(Tests_ArgumentsMapTest, suiteDescription_ArgumentsMapTest, 38, "testSet");

		// Initialize test suite: ClientTaskPlannerTest
		Tests_ClientTaskPlannerTest.initialize();

		_TS_TRY_WITH_SIGNAL_PROTECTION {
			_TS_TRY { suite_ClientTaskPlannerTest = new ClientTaskPlannerTest; } _TS_PROPAGATE_SIGNAL _TS_CATCH_ABORT( {} )
			_TS_LAST_CATCH( { CxxTest::__cxxtest_failed_init_suites.addSuite("ClientTaskPlannerTest", "Exception thrown when initializing " "ClientTaskPlannerTest"); } )
		} _TS_CATCH_SIGNAL( { CxxTest::__cxxtest_failed_init_suites.addSuite("ClientTaskPlannerTest", CxxTest::__cxxtest_sigmsg.c_str()); } );

		suiteDescription_ClientTaskPlannerTest.initialize(
			"Tests\\ClientTaskPlannerTest.h", 13,
			"ClientTaskPlannerTest", *suite_ClientTaskPlannerTest, Tests_ClientTaskPlannerTest);
		testDescription_ClientTaskPlannerTest_testAddTask.initialize(Tests_ClientTaskPlannerTest, suiteDescription_ClientTaskPlannerTest, 63, "testAddTask");
		testDescription_ClientTaskPlannerTest_testRun.initialize(Tests_ClientTaskPlannerTest, suiteDescription_ClientTaskPlannerTest, 75, "testRun");

		// Initialize test suite: ClientsMapTest
		Tests_ClientsMapTest.initialize();

		_TS_TRY_WITH_SIGNAL_PROTECTION {
			_TS_TRY { suite_ClientsMapTest = new ClientsMapTest; } _TS_PROPAGATE_SIGNAL _TS_CATCH_ABORT( {} )
			_TS_LAST_CATCH( { CxxTest::__cxxtest_failed_init_suites.addSuite("ClientsMapTest", "Exception thrown when initializing " "ClientsMapTest"); } )
		} _TS_CATCH_SIGNAL( { CxxTest::__cxxtest_failed_init_suites.addSuite("ClientsMapTest", CxxTest::__cxxtest_sigmsg.c_str()); } );

		suiteDescription_ClientsMapTest.initialize(
			"Tests\\ClientsMapTest.h", 8,
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
			"Tests\\LogTest.h", 9,
			"LogTest", *suite_LogTest, Tests_LogTest);
		testDescription_LogTest_testInit.initialize(Tests_LogTest, suiteDescription_LogTest, 12, "testInit");
		testDescription_LogTest_testAddrToStr.initialize(Tests_LogTest, suiteDescription_LogTest, 22, "testAddrToStr");
		testDescription_LogTest_testStrToAddr.initialize(Tests_LogTest, suiteDescription_LogTest, 30, "testStrToAddr");
		testDescription_LogTest_testIntToStr.initialize(Tests_LogTest, suiteDescription_LogTest, 38, "testIntToStr");
		testDescription_LogTest_testBoolToStr.initialize(Tests_LogTest, suiteDescription_LogTest, 43, "testBoolToStr");
		testDescription_LogTest_testStrToBool.initialize(Tests_LogTest, suiteDescription_LogTest, 49, "testStrToBool");

		// Initialize test suite: MDTaskTest
		Tests_MDTaskTest.initialize();

		_TS_TRY_WITH_SIGNAL_PROTECTION {
			_TS_TRY { suite_MDTaskTest = new MDTaskTest; } _TS_PROPAGATE_SIGNAL _TS_CATCH_ABORT( {} )
			_TS_LAST_CATCH( { CxxTest::__cxxtest_failed_init_suites.addSuite("MDTaskTest", "Exception thrown when initializing " "MDTaskTest"); } )
		} _TS_CATCH_SIGNAL( { CxxTest::__cxxtest_failed_init_suites.addSuite("MDTaskTest", CxxTest::__cxxtest_sigmsg.c_str()); } );

		suiteDescription_MDTaskTest.initialize(
			"Tests\\MDTaskTest.h", 10,
			"MDTaskTest", *suite_MDTaskTest, Tests_MDTaskTest);
		testDescription_MDTaskTest_testGetMD5.initialize(Tests_MDTaskTest, suiteDescription_MDTaskTest, 13, "testGetMD5");
		testDescription_MDTaskTest_testProcessing.initialize(Tests_MDTaskTest, suiteDescription_MDTaskTest, 21, "testProcessing");

		// Initialize test suite: MessageProcessorTest
		Tests_MessageProcessorTest.initialize();

		_TS_TRY_WITH_SIGNAL_PROTECTION {
			_TS_TRY { suite_MessageProcessorTest = new MessageProcessorTest; } _TS_PROPAGATE_SIGNAL _TS_CATCH_ABORT( {} )
			_TS_LAST_CATCH( { CxxTest::__cxxtest_failed_init_suites.addSuite("MessageProcessorTest", "Exception thrown when initializing " "MessageProcessorTest"); } )
		} _TS_CATCH_SIGNAL( { CxxTest::__cxxtest_failed_init_suites.addSuite("MessageProcessorTest", CxxTest::__cxxtest_sigmsg.c_str()); } );

		suiteDescription_MessageProcessorTest.initialize(
			"Tests\\MessageProcessorTest.h", 12,
			"MessageProcessorTest", *suite_MessageProcessorTest, Tests_MessageProcessorTest);
		testDescription_MessageProcessorTest_testRegisterProcessor.initialize(Tests_MessageProcessorTest, suiteDescription_MessageProcessorTest, 31, "testRegisterProcessor");
		testDescription_MessageProcessorTest_testProcessMessage.initialize(Tests_MessageProcessorTest, suiteDescription_MessageProcessorTest, 39, "testProcessMessage");

		// Initialize test suite: NodeTest
		Tests_NodeTest.initialize();

		_TS_TRY_WITH_SIGNAL_PROTECTION {
			_TS_TRY { suite_NodeTest = new NodeTest; } _TS_PROPAGATE_SIGNAL _TS_CATCH_ABORT( {} )
			_TS_LAST_CATCH( { CxxTest::__cxxtest_failed_init_suites.addSuite("NodeTest", "Exception thrown when initializing " "NodeTest"); } )
		} _TS_CATCH_SIGNAL( { CxxTest::__cxxtest_failed_init_suites.addSuite("NodeTest", CxxTest::__cxxtest_sigmsg.c_str()); } );

		suiteDescription_NodeTest.initialize(
			"Tests\\NodeTest.h", 8,
			"NodeTest", *suite_NodeTest, Tests_NodeTest);
		testDescription_NodeTest_testSendTask.initialize(Tests_NodeTest, suiteDescription_NodeTest, 45, "testSendTask");
		testDescription_NodeTest_testTaskComplete.initialize(Tests_NodeTest, suiteDescription_NodeTest, 56, "testTaskComplete");
		testDescription_NodeTest_testisThreadsAvalible.initialize(Tests_NodeTest, suiteDescription_NodeTest, 71, "testisThreadsAvalible");
		testDescription_NodeTest_testGetFreeThreadsNum.initialize(Tests_NodeTest, suiteDescription_NodeTest, 84, "testGetFreeThreadsNum");
		testDescription_NodeTest_testGetID.initialize(Tests_NodeTest, suiteDescription_NodeTest, 97, "testGetID");
		testDescription_NodeTest_testCheckForStaleTasks.initialize(Tests_NodeTest, suiteDescription_NodeTest, 105, "testCheckForStaleTasks");

		// Initialize test suite: NodesMapTest
		Tests_NodesMapTest.initialize();

		_TS_TRY_WITH_SIGNAL_PROTECTION {
			_TS_TRY { suite_NodesMapTest = new NodesMapTest; } _TS_PROPAGATE_SIGNAL _TS_CATCH_ABORT( {} )
			_TS_LAST_CATCH( { CxxTest::__cxxtest_failed_init_suites.addSuite("NodesMapTest", "Exception thrown when initializing " "NodesMapTest"); } )
		} _TS_CATCH_SIGNAL( { CxxTest::__cxxtest_failed_init_suites.addSuite("NodesMapTest", CxxTest::__cxxtest_sigmsg.c_str()); } );

		suiteDescription_NodesMapTest.initialize(
			"Tests\\NodesMapTest.h", 9,
			"NodesMapTest", *suite_NodesMapTest, Tests_NodesMapTest);
		testDescription_NodesMapTest_testRegisterNode.initialize(Tests_NodesMapTest, suiteDescription_NodesMapTest, 46, "testRegisterNode");
		testDescription_NodesMapTest_testUnregisterNode.initialize(Tests_NodesMapTest, suiteDescription_NodesMapTest, 58, "testUnregisterNode");
		testDescription_NodesMapTest_testGetNode.initialize(Tests_NodesMapTest, suiteDescription_NodesMapTest, 70, "testGetNode");
		testDescription_NodesMapTest_testGetThreadsNum.initialize(Tests_NodesMapTest, suiteDescription_NodesMapTest, 83, "testGetThreadsNum");
		testDescription_NodesMapTest_testTaskComplete.initialize(Tests_NodesMapTest, suiteDescription_NodesMapTest, 99, "testTaskComplete");

		// Initialize test suite: RequestTaskTest
		Tests_RequestTaskTest.initialize();

		_TS_TRY_WITH_SIGNAL_PROTECTION {
			_TS_TRY { suite_RequestTaskTest = new RequestTaskTest; } _TS_PROPAGATE_SIGNAL _TS_CATCH_ABORT( {} )
			_TS_LAST_CATCH( { CxxTest::__cxxtest_failed_init_suites.addSuite("RequestTaskTest", "Exception thrown when initializing " "RequestTaskTest"); } )
		} _TS_CATCH_SIGNAL( { CxxTest::__cxxtest_failed_init_suites.addSuite("RequestTaskTest", CxxTest::__cxxtest_sigmsg.c_str()); } );

		suiteDescription_RequestTaskTest.initialize(
			"Tests\\RequestTaskTest.h", 8,
			"RequestTaskTest", *suite_RequestTaskTest, Tests_RequestTaskTest);
		testDescription_RequestTaskTest_testRequest.initialize(Tests_RequestTaskTest, suiteDescription_RequestTaskTest, 11, "testRequest");

		// Initialize test suite: ServerTaskPlannerTest
		Tests_ServerTaskPlannerTest.initialize();

		_TS_TRY_WITH_SIGNAL_PROTECTION {
			_TS_TRY { suite_ServerTaskPlannerTest = new ServerTaskPlannerTest; } _TS_PROPAGATE_SIGNAL _TS_CATCH_ABORT( {} )
			_TS_LAST_CATCH( { CxxTest::__cxxtest_failed_init_suites.addSuite("ServerTaskPlannerTest", "Exception thrown when initializing " "ServerTaskPlannerTest"); } )
		} _TS_CATCH_SIGNAL( { CxxTest::__cxxtest_failed_init_suites.addSuite("ServerTaskPlannerTest", CxxTest::__cxxtest_sigmsg.c_str()); } );

		suiteDescription_ServerTaskPlannerTest.initialize(
			"Tests\\ServerTaskPlannerTest.h", 11,
			"ServerTaskPlannerTest", *suite_ServerTaskPlannerTest, Tests_ServerTaskPlannerTest);
		testDescription_ServerTaskPlannerTest_testAddTask.initialize(Tests_ServerTaskPlannerTest, suiteDescription_ServerTaskPlannerTest, 14, "testAddTask");
		testDescription_ServerTaskPlannerTest_testTaskComplete.initialize(Tests_ServerTaskPlannerTest, suiteDescription_ServerTaskPlannerTest, 22, "testTaskComplete");
		testDescription_ServerTaskPlannerTest_testGetTask.initialize(Tests_ServerTaskPlannerTest, suiteDescription_ServerTaskPlannerTest, 32, "testGetTask");

		// Initialize test suite: TaskMessageTest
		Tests_TaskMessageTest.initialize();

		_TS_TRY_WITH_SIGNAL_PROTECTION {
			_TS_TRY { suite_TaskMessageTest = new TaskMessageTest; } _TS_PROPAGATE_SIGNAL _TS_CATCH_ABORT( {} )
			_TS_LAST_CATCH( { CxxTest::__cxxtest_failed_init_suites.addSuite("TaskMessageTest", "Exception thrown when initializing " "TaskMessageTest"); } )
		} _TS_CATCH_SIGNAL( { CxxTest::__cxxtest_failed_init_suites.addSuite("TaskMessageTest", CxxTest::__cxxtest_sigmsg.c_str()); } );

		suiteDescription_TaskMessageTest.initialize(
			"Tests\\TaskMessageTest.h", 8,
			"TaskMessageTest", *suite_TaskMessageTest, Tests_TaskMessageTest);
		testDescription_TaskMessageTest_testRequest.initialize(Tests_TaskMessageTest, suiteDescription_TaskMessageTest, 12, "testRequest");
		testDescription_TaskMessageTest_testRequestCancel.initialize(Tests_TaskMessageTest, suiteDescription_TaskMessageTest, 29, "testRequestCancel");
		testDescription_TaskMessageTest_testRespond.initialize(Tests_TaskMessageTest, suiteDescription_TaskMessageTest, 45, "testRespond");
		testDescription_TaskMessageTest_testRespondCancel.initialize(Tests_TaskMessageTest, suiteDescription_TaskMessageTest, 63, "testRespondCancel");

		// Initialize test suite: TaskPlannerTest
		Tests_TaskPlannerTest.initialize();

		_TS_TRY_WITH_SIGNAL_PROTECTION {
			_TS_TRY { suite_TaskPlannerTest = new TaskPlannerTest; } _TS_PROPAGATE_SIGNAL _TS_CATCH_ABORT( {} )
			_TS_LAST_CATCH( { CxxTest::__cxxtest_failed_init_suites.addSuite("TaskPlannerTest", "Exception thrown when initializing " "TaskPlannerTest"); } )
		} _TS_CATCH_SIGNAL( { CxxTest::__cxxtest_failed_init_suites.addSuite("TaskPlannerTest", CxxTest::__cxxtest_sigmsg.c_str()); } );

		suiteDescription_TaskPlannerTest.initialize(
			"Tests\\TaskPlannerTest.h", 10,
			"TaskPlannerTest", *suite_TaskPlannerTest, Tests_TaskPlannerTest);
		testDescription_TaskPlannerTest_testAddTask.initialize(Tests_TaskPlannerTest, suiteDescription_TaskPlannerTest, 45, "testAddTask");
		testDescription_TaskPlannerTest_testTaskComplete.initialize(Tests_TaskPlannerTest, suiteDescription_TaskPlannerTest, 57, "testTaskComplete");

		// Initialize test suite: UnitTestTask
		Tests_UnitTestTask.initialize();

		_TS_TRY_WITH_SIGNAL_PROTECTION {
			_TS_TRY { suite_UnitTestTask = new UnitTestTask; } _TS_PROPAGATE_SIGNAL _TS_CATCH_ABORT( {} )
			_TS_LAST_CATCH( { CxxTest::__cxxtest_failed_init_suites.addSuite("UnitTestTask", "Exception thrown when initializing " "UnitTestTask"); } )
		} _TS_CATCH_SIGNAL( { CxxTest::__cxxtest_failed_init_suites.addSuite("UnitTestTask", CxxTest::__cxxtest_sigmsg.c_str()); } );

		suiteDescription_UnitTestTask.initialize(
			"Tests\\TestTask.h", 7,
			"UnitTestTask", *suite_UnitTestTask, Tests_UnitTestTask);
		testDescription_UnitTestTask_testRequest.initialize(Tests_UnitTestTask, suiteDescription_UnitTestTask, 42, "testRequest");
		testDescription_UnitTestTask_testRespond.initialize(Tests_UnitTestTask, suiteDescription_UnitTestTask, 59, "testRespond");
		testDescription_UnitTestTask_testPlannerID.initialize(Tests_UnitTestTask, suiteDescription_UnitTestTask, 76, "testPlannerID");

		// Initialize test suite: TestTaskTest
		Tests_TestTaskTest.initialize();

		_TS_TRY_WITH_SIGNAL_PROTECTION {
			_TS_TRY { suite_TestTaskTest = new TestTaskTest; } _TS_PROPAGATE_SIGNAL _TS_CATCH_ABORT( {} )
			_TS_LAST_CATCH( { CxxTest::__cxxtest_failed_init_suites.addSuite("TestTaskTest", "Exception thrown when initializing " "TestTaskTest"); } )
		} _TS_CATCH_SIGNAL( { CxxTest::__cxxtest_failed_init_suites.addSuite("TestTaskTest", CxxTest::__cxxtest_sigmsg.c_str()); } );

		suiteDescription_TestTaskTest.initialize(
			"Tests\\TestTaskTest.h", 8,
			"TestTaskTest", *suite_TestTaskTest, Tests_TestTaskTest);
		testDescription_TestTaskTest_testProcess.initialize(Tests_TestTaskTest, suiteDescription_TestTaskTest, 11, "testProcess");
		testDescription_TestTaskTest_testSeperateTask.initialize(Tests_TestTaskTest, suiteDescription_TestTaskTest, 18, "testSeperateTask");

		// Initialize test suite: TinyXmlTest
		Tests_TinyXmlTest.initialize();

		_TS_TRY_WITH_SIGNAL_PROTECTION {
			_TS_TRY { suite_TinyXmlTest = new TinyXmlTest; } _TS_PROPAGATE_SIGNAL _TS_CATCH_ABORT( {} )
			_TS_LAST_CATCH( { CxxTest::__cxxtest_failed_init_suites.addSuite("TinyXmlTest", "Exception thrown when initializing " "TinyXmlTest"); } )
		} _TS_CATCH_SIGNAL( { CxxTest::__cxxtest_failed_init_suites.addSuite("TinyXmlTest", CxxTest::__cxxtest_sigmsg.c_str()); } );

		suiteDescription_TinyXmlTest.initialize(
			"Tests\\TinyXmlTest.h", 8,
			"TinyXmlTest", *suite_TinyXmlTest, Tests_TinyXmlTest);
		testDescription_TinyXmlTest_testTinyXML.initialize(Tests_TinyXmlTest, suiteDescription_TinyXmlTest, 11, "testTinyXML");

		// Initialize test suite: XMLUtilsTest
		Tests_XMLUtilsTest.initialize();

		_TS_TRY_WITH_SIGNAL_PROTECTION {
			_TS_TRY { suite_XMLUtilsTest = new XMLUtilsTest; } _TS_PROPAGATE_SIGNAL _TS_CATCH_ABORT( {} )
			_TS_LAST_CATCH( { CxxTest::__cxxtest_failed_init_suites.addSuite("XMLUtilsTest", "Exception thrown when initializing " "XMLUtilsTest"); } )
		} _TS_CATCH_SIGNAL( { CxxTest::__cxxtest_failed_init_suites.addSuite("XMLUtilsTest", CxxTest::__cxxtest_sigmsg.c_str()); } );

		suiteDescription_XMLUtilsTest.initialize(
			"Tests\\XMLUtilsTest.h", 8,
			"XMLUtilsTest", *suite_XMLUtilsTest, Tests_XMLUtilsTest);
		testDescription_XMLUtilsTest_testAddPacketID.initialize(Tests_XMLUtilsTest, suiteDescription_XMLUtilsTest, 11, "testAddPacketID");
		testDescription_XMLUtilsTest_testAddText.initialize(Tests_XMLUtilsTest, suiteDescription_XMLUtilsTest, 20, "testAddText");
		testDescription_XMLUtilsTest_testAddInt.initialize(Tests_XMLUtilsTest, suiteDescription_XMLUtilsTest, 32, "testAddInt");
		testDescription_XMLUtilsTest_testGetText.initialize(Tests_XMLUtilsTest, suiteDescription_XMLUtilsTest, 42, "testGetText");
		testDescription_XMLUtilsTest_testGetInt.initialize(Tests_XMLUtilsTest, suiteDescription_XMLUtilsTest, 51, "testGetInt");
		testDescription_XMLUtilsTest_testGetPacketId.initialize(Tests_XMLUtilsTest, suiteDescription_XMLUtilsTest, 61, "testGetPacketId");
		testDescription_XMLUtilsTest_testPacketId.initialize(Tests_XMLUtilsTest, suiteDescription_XMLUtilsTest, 71, "testPacketId");
		testDescription_XMLUtilsTest_testBool.initialize(Tests_XMLUtilsTest, suiteDescription_XMLUtilsTest, 84, "testBool");


	}
	
	void cleanup()
	{
		delete suite_ArgumentsMapTest;
		delete suite_ClientTaskPlannerTest;
		delete suite_ClientsMapTest;
		delete suite_LogTest;
		delete suite_MDTaskTest;
		delete suite_MessageProcessorTest;
		delete suite_NodeTest;
		delete suite_NodesMapTest;
		delete suite_RequestTaskTest;
		delete suite_ServerTaskPlannerTest;
		delete suite_TaskMessageTest;
		delete suite_TaskPlannerTest;
		delete suite_UnitTestTask;
		delete suite_TestTaskTest;
		delete suite_TinyXmlTest;
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



