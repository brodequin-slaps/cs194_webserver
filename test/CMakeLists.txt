#Standalone unit tests definition

cmake_minimum_required(VERSION 3.10)
project(cs194_webserverTests)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#dependencies
include(CTest)

#needed to have access to our own project headers
include_directories(..)

#find_package(GTest MODULE REQUIRED)

#here, we only want to find package if we run the standalone tests.
#if we are being run from top level, we already know about cs194_webserver package
#and we wont enter in the if branch.

#if(NOT TARGET geranim0::cs194_webserver)
#    find_package(cs194_webserver CONFIG REQUIRED)
#endif()
#
##target definition
#add_executable(cs194_webserverTests tests.cpp)
#target_link_libraries(cs194_webserverTest
#    PRIVATE
#        geranim0::cs194_webserver
#        GTest::Main
#)
#
#add_test(NAME cs194_webserver.UnitTests
#    COMMAND cs194_webserverTests
#)


#testing testing
#enable_testing()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(
    cs194_webserverTests
    main.test.cpp
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${CONAN_LIBS})

include(GoogleTest)
gtest_discover_tests(cs194_webserverTests)