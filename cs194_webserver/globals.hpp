#pragma once

#include <atomic>

extern std::atomic<int> keepRunning;
extern std::mutex print_seq_mtx;
static constexpr bool g_print_debug = true;