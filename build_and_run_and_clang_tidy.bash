#!/bin/bash

./build.xsh --build_dir cs194_webserver --build_missing_conan --build_type Release

if [ $? -ne 0 ]; then
echo Compilation failed
else
echo Compilation success, running cs194_webserver
(cd cs194_webserver/build/Release/bin/ ; ./cs194_webserver)
fi