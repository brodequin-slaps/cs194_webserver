#pragma once

#include <iostream>
#include <sstream>
#include <fstream>

//templates
template<typename... Ts>
void printerr(Ts... args)
{
    (std::cerr << ... << args) << std::endl;
}

//non templates
std::string_view get_rq_file(std::string_view rq);
std::string read_whole_file(std::ifstream& istrm);