#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <mutex>
#include "globals.hpp"

//templates
template<typename... Ts>
void print_impl(std::ostream& os, Ts... args)
{
    (os << ... << args);
}

//templates
template<typename... Ts>
void println(std::ostream& os, Ts... args)
{
    print_impl(os, args..., '\n');
}

template<typename... Ts>
void printerr(Ts... args)
{
    std::lock_guard<std::mutex> lock(print_seq_mtx);
    println(std::cerr, args...);
}

template<typename... Ts>
void print(Ts... args)
{
    std::lock_guard<std::mutex> lock(print_seq_mtx);
    println(std::cout, args...);
}

template<typename... Ts>
void print_debug(Ts... args)
{
    if constexpr (g_print_debug == true)
    {
        std::lock_guard<std::mutex> lock(print_seq_mtx);
        println(std::cout, args...);
    }    
}

//non templates
std::string_view get_rq_file(std::string_view rq);
std::string read_whole_file(std::ifstream& istrm);