#include <iostream>
#include <signal.h>
#include <filesystem>


#include "webserver_simple_sync.hpp" 
#include "webserver_dumb.hpp"
#include "utils.hpp"
#include "globals.hpp"

std::atomic<int> keepRunning = 1;

void intHandler(int)
{
    keepRunning = 0;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printerr("Usage: ./server <serving directory>");
        exit(1);
    }

    std::filesystem::path path{argv[1]};

    signal(SIGINT, intHandler);
    //webserver_simple_sync();
    //webserver_echo();
    webserver_dir(path);

    return 0;
}