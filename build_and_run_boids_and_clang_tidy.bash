#!/bin/bash

./build.xsh --build_dir gtest_conan_cmake_template --build_missing_conan --build_type Release

if [ $? -ne 0 ]; then
echo Compilation failed
else
echo Compilation success, running gtest_conan_cmake_template
(cd gtest_conan_cmake_template/build/Release/bin/ ; ./gtest_conan_cmake_template)
fi