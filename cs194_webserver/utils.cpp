#include "utils.hpp"

std::string_view get_rq_file(std::string_view rq)
{
    auto first_space = rq.find(' ', 0);
    auto second_space = rq.find(' ', first_space + 1);
    return rq.substr(first_space+1, second_space-first_space-1);
}

std::string read_whole_file(std::ifstream& istrm)
{
    std::ostringstream ss;
    ss << istrm.rdbuf();
    return ss.str();
}