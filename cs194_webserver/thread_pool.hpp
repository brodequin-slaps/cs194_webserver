#pragma once

#include <stddef.h>
#include <array>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <chrono>
#include <string.h>

#include "circular_buffer.hpp"

// the code fails with every other type. why???
using __atomic_type = int32_t;

template<size_t thread_circular_buf_sz>
void thread_worker(circular_buffer<std::function<void()>, thread_circular_buf_sz>* work_circular_buf, std::atomic<__atomic_type>* terminated)
{
    while(terminated->load() != 1)
    {
        //wait for some work to be available
        while (true)
        {
            std::unique_lock<std::mutex> lk(work_circular_buf->cv_m);
            work_circular_buf->cv.wait_for(lk, std::chrono::seconds(1));

            if (work_circular_buf->get_size() > 0 || terminated->load() == 1)
            {
                break;
            }
        }

        //while (begin != end), execute workloads and update (begin) to (begin + 1)
        while (work_circular_buf->get_begin() != work_circular_buf->get_end())
        {
            auto& workload = work_circular_buf->front();
            workload();
            work_circular_buf->delete_front();
        }
    }
}

template<size_t nb_threads>
class thread_pool
{
public:
    thread_pool()
    {
        for (size_t i = 0; i < nb_threads; i++)
        {
            thread_sync_arr[i].store(0);
            threads_ptrs[i] = new std::thread{thread_worker<thread_circular_buf_sz>, &function_queues[i], &thread_sync_arr[i]};
        }
    }

    //simple. if someone else calls do_work at the same time, it will not be executed
    ~thread_pool()
    {
        for (size_t i = 0; i < nb_threads; i++)
        {
            thread_sync_arr[i].store(1);
        }

        for (size_t i = 0; i < nb_threads; i++)
        {
            threads_ptrs[i]->join();
            delete threads_ptrs[i];
        }
    }

    void do_work(std::function<void()> fn)
    {
        //find thread with lowest queue size
        int work_thread_index = find_lowest_queue_size_thread_index();

        if (work_thread_index == -1)
        {
            printerr("all thread queues full. skipping");
        }
        else
        {
            print_debug("do_work: chosen thread = ", work_thread_index);

            //add work to thread queue
            function_queues[work_thread_index].push_back(fn);
        }
    }

private:
    static constexpr size_t thread_circular_buf_sz = 1024;
    std::array<circular_buffer<std::function<void()>, thread_circular_buf_sz>, nb_threads> function_queues;
    std::array<std::thread*, nb_threads> threads_ptrs;
    std::array<std::function<void()>, nb_threads> thread_work_arr;
    alignas(256) std::array<std::atomic<__atomic_type>, nb_threads> thread_sync_arr; // synchronisation
    std::array<std::atomic<__atomic_type>, nb_threads> thread_terminate_arr;

    int find_lowest_queue_size_thread_index()
    {
        int index = -1;
        size_t min = thread_circular_buf_sz;
        for (int i = 0; (size_t)i < nb_threads; i++)
        {
            auto queue_sz = function_queues[i].get_size();
            if (queue_sz == 0)
            {
                return i;
            }
            else if (queue_sz < min)
            {
                index = i;
                min = queue_sz;
            }
        }
        return index;
    }
};