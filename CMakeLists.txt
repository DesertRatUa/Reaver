cmake_minimum_required(VERSION 2.8.4)
project(Reaver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories( "/" )
include_directories( "C:/MinGW/x86_64-w64-mingw32/include" )
include_directories( "C:/MinGW/boost" )
LINK_DIRECTORIES( "C:/MinGW/boost/libs" )
LINK_DIRECTORIES( "C:/MinGW/lib" )
#include_directories( "C:/MinGW/include" )

add_definitions(-DWIN64)

set(SOURCE_FILES
    Messages/EchoMessage.cpp
    Messages/EchoMessage.h
    Messages/Message.cpp
    Messages/Message.h
    Messages/RegisterMessage.cpp
    Messages/RegisterMessage.h
    Messages/TaskMessage.cpp
    Messages/TaskMessage.h
    Messages/RequestTask.h
    Messages/RequestTask.cpp
    Tasks/MD5Task.cpp
    Tasks/MD5Task.h
    Tasks/Task.cpp
    Tasks/Task.h
    Tasks/TestTask.cpp
    Tasks/TestTask.h
    Tests/ArgumentsMapTest.h
    Tests/ClientsMapTest.h
    Tests/ClientTaskPlannerTest.h
    Tests/LogTest.h
    Tests/MDTaskTest.h
    Tests/MessageProcessorTest.h
    Tests/NodesMapTest.h
    Tests/NodeTest.h
    Tests/TaskMessageTest.h
    Tests/TaskPlannerTest.h
    Tests/TestTask.h
    Tests/TestTaskTest.h
    Tests/TinyXmlTest.h
    Tests/xmltest.cpp
    Tests/xmltest.h
    Tests/XMLUtilsTest.h
    Argument.cpp
    Argument.h
    ArgumentsMap.cpp
    ArgumentsMap.h
    Client.cpp
    Client.h
    ClientCommunicationManager.cpp
    ClientCommunicationManager.h
    ClientMessageProcessor.cpp
    ClientMessageProcessor.h
    ClientModule.cpp
    ClientModule.h
    ClientsMap.cpp
    ClientsMap.h
    ClientTaskPlanner.cpp
    ClientTaskPlanner.h
    CommunicationManager.cpp
    CommunicationManager.h
    Config.cpp
    Config.h
    include.h
    Log.cpp
    Log.h
    main.cpp
    MessageProcessor.cpp
    MessageProcessor.h
    Module.cpp
    Module.h
    Node.cpp
    Node.h
    NodesMap.cpp
    NodesMap.h
    #runAllTests.cpp
    ServerCommunicationManager.cpp
    ServerCommunicationManager.h
    ServerMessageProcessor.cpp
    ServerMessageProcessor.h
    ServerModule.cpp
    ServerModule.h
    ServerTaskPlanner.cpp
    ServerTaskPlanner.h
    SignalHandler.cpp
    SignalHandler.h
    Thread.h
    tinyxml2.cpp
    tinyxml2.h
    #UnitTest.cpp
    #UnitTest.h
    XMLUtils.cpp
    XMLUtils.h
    )

add_executable(Reaver ${SOURCE_FILES})

add_library(cypto STATIC IMPORTED)
set_property(TARGET cypto PROPERTY IMPORTED_LOCATION "C:/MinGW/x86_64-w64-mingw32/lib/libcrypto.a")

add_library(ws2 STATIC IMPORTED)
set_property(TARGET ws2 PROPERTY IMPORTED_LOCATION "C:/MinGW/x86_64-w64-mingw32/lib/libws2_32.a")

target_link_libraries(Reaver cypto ws2)