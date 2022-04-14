
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h> // sockaddr_in
#include <sstream>
#include <fstream>
#include <cstring>
#include <thread>
#include <array>

#include "utils.hpp"
#include "globals.hpp"
#include "constants.hpp"
#include "webserver_thread_pool.hpp"
#include "thread_pool.hpp"

using namespace std;

static void thread_work(int client_sockid, filesystem::path path)
{
    int status;
    char recvbuf[recvbuf_sz];
    int count = recv(client_sockid, recvbuf, recvbuf_sz, 0);

    for (int i = 0; i < count; i++)
    {
        std::cout << recvbuf[i];
    }
    std::cout << std::endl;

    auto recv_sv = string_view{recvbuf};

    string_view rq_file = get_rq_file(recv_sv);

    string rq_file_str{rq_file};

    string new_path = path.string() + rq_file_str;

    ifstream istrm{new_path};

    if (!istrm.is_open())
    {
        printerr("Error opening file: ", new_path, " : ", strerror(errno));
        exit(1);
    }

    string file_content = read_whole_file(istrm);

    istrm.close();

    stringstream resp;

    resp << "HTTP/1.1 200 OK\r\n"
        << "Content-Length: " << file_content.size() << "\r\n"
        << "Content-Type: text/plain\r\n\r\n"
        << file_content << endl;

    count = send(client_sockid, resp.str().c_str() , resp.str().size(), 0);

    status = close(client_sockid);
    if (status != 0)
    {
        printerr("socket close operation failed with code: ", status, ": ", strerror(errno));
        exit(1);
    }
}

void webserver_thread_pool(std::filesystem::path path)
{
    thread_pool<128> thr_pool;

    auto fn = [](int i){
        sleep(1);
        print("from thread #", i);
    };

    for (int i = 0; i < 15; i++)
    {
       thr_pool.do_work([i, fn](){
            fn(i);
        });
    }

    
    int status;

    sockaddr_in addrport;
    addrport.sin_family = AF_INET;
    addrport.sin_port = htons(10666);
    addrport.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    //0 for protocol -> use default
    int sockid = socket(PF_INET, SOCK_STREAM, 0);
    if (sockid == -1)
    {
        printerr("socket creation failure");
        return;   
    }

    //so we can stop and start it very often without getting
    //bind - already in use - errors.
    // see https://stackoverflow.com/questions/15198834/bind-failed-address-already-in-use
    int enable = 1;
    if (setsockopt(sockid, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    {
        printerr("setsockopt(SO_REUSEADDR) failed");
    }

    status = bind(sockid, reinterpret_cast<sockaddr const*>(&addrport), sizeof(sockaddr_in));
    if (status == -1)
    {
        printerr("bind failure with error number ", strerror(errno));
        return;
    }

    status = listen(sockid, queuelimit);
    if (status == -1)
    {
        printerr("listen failure");
        return;
    }

    while (keepRunning == 1)
    {
        sockaddr clientAddr;
        socklen_t addrLen = sizeof(sockaddr);
        int client_sockid = accept(sockid, &clientAddr, &addrLen);

        thr_pool.do_work([client_sockid, &path](){
            thread_work(client_sockid, path);
        });
    }

    //closes the connection (for stream sockets) and frees up the used port
    status = close(sockid);
    if (status != 0)
    {
        printerr("socket close operation failed with code: ", status);
        return;
    }
}