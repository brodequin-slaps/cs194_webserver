add_test( Dummy.dummytest1 /home/sam/development/UniqueProjectName/test/build/Release/bin/gtest_conan_cmake_templateTests [==[--gtest_filter=Dummy.dummytest1]==] --gtest_also_run_disabled_tests)
set_tests_properties( Dummy.dummytest1 PROPERTIES WORKING_DIRECTORY /home/sam/development/UniqueProjectName/test/build/Release)
set( gtest_conan_cmake_templateTests_TESTS Dummy.dummytest1)
