#pragma once

#include <array>
#include <atomic>
#include <condition_variable>
#include <chrono>
#include <unistd.h>

//using uint32_t because its the only type that seems to work with futexes
//todo: write something to put an error if buf_sz <=2
template<typename T, uint32_t buf_sz>
class circular_buffer
{
public:
    circular_buffer() : begin{0}, end{0}
    {

    }

    //to be called in do_work (which is anywhere anytime)
    int push_back(T const& elem)
    {
        std::lock_guard<std::mutex> lk(push_back_mtx);
        
        size_t next_end_idx = (end + 1) % buf_sz;

        if (next_end_idx != begin) // 1 empty space in our array because (begin == end) means empty
        {
            arr[end] = elem;
            end = next_end_idx;
            cv.notify_one();
            return 0;
        }
        else
        {
            return 1;
        }
    }

    //to be called within working thread
    int delete_front()
    {
        if (begin != end)
        {
            begin = (begin + 1) % buf_sz;
            return 0;
        }
        else
        {
            return 1;
        }
    }

    uint32_t get_size()
    {
        int diff = end - begin;
        if (diff < 0)
        {
            return buf_sz + diff;
        }
        else
        {
            return diff;
        }
    }

    uint64_t get_begin()
    {
        return begin;
    }

    uint64_t get_end()
    {
        return end;
    }

    T& front()
    {
        return arr[begin];
    }

    std::condition_variable cv;
    std::mutex cv_m;
private:
    std::array<T, buf_sz> arr;
    uint64_t begin;
    uint64_t end;
    std::mutex push_back_mtx;
};