#include <iostream>
#include <string_view>

#include "dumb_clients.hpp"


int main(int argc, char* argv[])
{
    if (argc >= 2)
    {
        tcpclient(argv[1]);
    }
    else
    {
        std::cerr << "please provide argument" << std::endl;
    }
    return 0;
}