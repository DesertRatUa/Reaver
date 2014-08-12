/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
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
CxxTest::StaticSuiteDescription suiteDescription_UnitTest( "UnitTest.h", 6, "UnitTest", suite_UnitTest, Tests_UnitTest );

static class TestDescription_suite_UnitTest_testAddition : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_UnitTest_testAddition() : CxxTest::RealTestDescription( Tests_UnitTest, suiteDescription_UnitTest, 9, "testAddition" ) {}
 void runTest() { suite_UnitTest.testAddition(); }
} testDescription_suite_UnitTest_testAddition;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
