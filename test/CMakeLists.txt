#Standalone unit tests definition

cmake_minimum_required(VERSION 3.10)
project(gtest_conan_cmake_templateTests)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#dependencies
include(CTest)

#needed to have access to our own project headers
include_directories(..)

#find_package(GTest MODULE REQUIRED)

#here, we only want to find package if we run the standalone tests.
#if we are being run from top level, we already know about gtest_conan_cmake_template package
#and we wont enter in the if branch.

#if(NOT TARGET geranim0::gtest_conan_cmake_template)
#    find_package(gtest_conan_cmake_template CONFIG REQUIRED)
#endif()
#
##target definition
#add_executable(gtest_conan_cmake_templateTests tests.cpp)
#target_link_libraries(gtest_conan_cmake_templateTest
#    PRIVATE
#        geranim0::gtest_conan_cmake_template
#        GTest::Main
#)
#
#add_test(NAME gtest_conan_cmake_template.UnitTests
#    COMMAND gtest_conan_cmake_templateTests
#)


#testing testing
#enable_testing()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(
    gtest_conan_cmake_templateTests
    main.test.cpp
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${CONAN_LIBS})

include(GoogleTest)
gtest_discover_tests(gtest_conan_cmake_templateTests)