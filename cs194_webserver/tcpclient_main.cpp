#include <iostream>
#include <string_view>

#include "dumb_clients.hpp"


constexpr long nb_rq = 100000;

int main(int argc, char* argv[])
{
    if (argc >= 2)
    {
        for (long i = 0; i < nb_rq; i++)
        {
           tcpclient(argv[1]); 
        }
    }
    else
    {
        std::cerr << "please provide argument" << std::endl;
    }
    return 0;
}