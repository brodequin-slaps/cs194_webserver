#include "globals.hpp"

std::atomic<int> keepRunning = 1;
std::mutex print_seq_mtx;