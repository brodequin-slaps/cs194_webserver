#!/bin/bash

export CC=/usr/bin/gcc-11
export CXX=/usr/bin/g++-11

conan_profile_path=~/.conan/profiles/default

./build.xsh --build_dir cs194_webserver --build_missing_conan --build_type Debug --conan_profile $conan_profile_path
