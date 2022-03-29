#Standalone library definition and installation
#Does not change compiler warnings!

cmake_minimum_required(VERSION 3.10)

# set the project name
project(cs194_webserver VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra -pedantic -fno-exceptions
    "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
    "$<$<CONFIG:RELEASE>:-Ofast>")

#run clang-tidy
#set(CMAKE_CXX_CLANG_TIDY 
#    clang-tidy;
#    -checks=-cppcoreguidelines-avoid-magic-numbers; #everything but magic numbers
#    -header-filter=.*;)

#needed to have access to our own project headers
include_directories(..)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# add the executable
add_executable(cs194_webserver 
    webserver_main.cpp 
    webserver_simple_sync.cpp
    webserver_dumb.cpp
    utils.cpp
)

add_executable(cs194_tcpclient
    tcpclient_main.cpp
    dumb_clients.cpp
    utils.cpp
)

add_executable(cs194_udpclient
    udpclient_main.cpp
    dumb_clients.cpp
    utils.cpp
)

#link to conan libs
target_link_libraries(cs194_webserver ${CONAN_LIBS})
