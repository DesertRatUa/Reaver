/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_UnitTest_init = false;
#include "UnitTest.h"

static UnitTest suite_UnitTest;

static CxxTest::List Tests_UnitTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_UnitTest( "UnitTest.h", 13, "UnitTest", suite_UnitTest, Tests_UnitTest );

static class TestDescription_suite_UnitTest_TestClientMessageProcessor : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_UnitTest_TestClientMessageProcessor() : CxxTest::RealTestDescription( Tests_UnitTest, suiteDescription_UnitTest, 16, "TestClientMessageProcessor" ) {}
 void runTest() { suite_UnitTest.TestClientMessageProcessor(); }
} testDescription_suite_UnitTest_TestClientMessageProcessor;

static class TestDescription_suite_UnitTest_TestLog : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_UnitTest_TestLog() : CxxTest::RealTestDescription( Tests_UnitTest, suiteDescription_UnitTest, 31, "TestLog" ) {}
 void runTest() { suite_UnitTest.TestLog(); }
} testDescription_suite_UnitTest_TestLog;

static class TestDescription_suite_UnitTest_TestArgumentMap : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_UnitTest_TestArgumentMap() : CxxTest::RealTestDescription( Tests_UnitTest, suiteDescription_UnitTest, 47, "TestArgumentMap" ) {}
 void runTest() { suite_UnitTest.TestArgumentMap(); }
} testDescription_suite_UnitTest_TestArgumentMap;

static class TestDescription_suite_UnitTest_TestPacketId : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_UnitTest_TestPacketId() : CxxTest::RealTestDescription( Tests_UnitTest, suiteDescription_UnitTest, 60, "TestPacketId" ) {}
 void runTest() { suite_UnitTest.TestPacketId(); }
} testDescription_suite_UnitTest_TestPacketId;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
