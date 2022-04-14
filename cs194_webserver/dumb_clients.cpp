#include <arpa/inet.h> // sockaddr_in
#include <string_view>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "globals.hpp"
#include "utils.hpp"
#include "dumb_clients.hpp"

using namespace std;

constexpr unsigned long recvbuf_sz = 65536;

void tcpclient(string_view msg)
{
    int status;

    sockaddr_in addrport;
    addrport.sin_family = AF_INET;
    addrport.sin_port = htons(10666);
    addrport.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    //0 for protocol -> use default
    int sockid = socket(PF_INET, SOCK_STREAM, 0);
    if (sockid == -1)
    {
        printerr("Socket creation failure: ", strerror(errno));
        return;   
    }

    status = connect(sockid, reinterpret_cast<sockaddr const*>(&addrport), sizeof(sockaddr));
    if (status == -1)
    {
        printerr("connect failure: ", strerror(errno));
        return;   
    }

    int count = send(sockid, msg.data(), msg.size(), 0);

    //recv the servers answer
    char recvbuf[recvbuf_sz];
    count = recv(sockid, recvbuf, recvbuf_sz, 0);
    
    /*cout << "received: " << endl;
    for (int i = 0; i < count; i++)
    {
        std::cout << recvbuf[i];
    }
    cout << endl;*/

    close(sockid);
}

void udpclient()
{
    
}