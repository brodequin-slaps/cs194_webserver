#include <iostream>
#include <signal.h>
#include <filesystem>

#include "webserver_thread_pool.hpp"
#include "webserver_thread_per_client.hpp"
#include "webserver_process_per_client.hpp"
#include "webserver_simple_sync.hpp" 
#include "webserver_dumb.hpp"
#include "utils.hpp"
#include "globals.hpp"
#include "webserver_asio.hpp"

void intHandler(int)
{
    keepRunning = 0;
}

#include <vector>
int longestTradingSeriesAtOnlyTwoPrices(std::vector<int> tradePrices) {
    
    if (tradePrices.size() <= 2)
    {
        return tradePrices.size();
    }
    
    int max_series_length = -1;
    int max_series_start_index = 0;
    int same_number_sequence_start_index;
    
    int current_series_start_index = 0;
    int current_series_length = 2;
    int series_price_1 = tradePrices[0];
    int series_price_2 = tradePrices[1];
    
    if (series_price_1 == series_price_2)
    {
        same_number_sequence_start_index = 0;
    }
    else 
    {
        same_number_sequence_start_index = 1;
    }
    
    for (int i = 2; i < tradePrices.size(); i++)
    {   
        if (tradePrices[i] == series_price_1 || tradePrices[i] == series_price_2)
        {
            ++current_series_length;
        }
        else
        {
            if (current_series_length > max_series_length)
            {
                max_series_length = current_series_length;
                max_series_start_index = current_series_start_index;
            }
            current_series_start_index = same_number_sequence_start_index;
            current_series_length = i - same_number_sequence_start_index + 1;
            series_price_1 = series_price_2;
            series_price_2 = tradePrices[i];
        }

        if (tradePrices[i] != tradePrices[i-1])
        {
            same_number_sequence_start_index = i;
        }
    }
    
    if (current_series_length > max_series_length)
    {
        max_series_length = current_series_length;
        max_series_start_index = current_series_start_index;
    }

    return max_series_start_index;
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
    //webserver_dir(path);
    //webserver_process_per_client(path);
    //webserver_thread_per_client(path);
    //webserver_thread_pool(path);
    //webserver_asio(path);

    int res = longestTradingSeriesAtOnlyTwoPrices({1,2,1,2,3,4,3,4});

    return 0;
}