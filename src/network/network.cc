#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#include "network/network.hh"

Network *Network::instance = NULL;

Network::Network(void)
    : server_sock(0)
{
}

Network::~Network(void)
{
}

Network *Network::getInstance(void)
{
    if (!this->instance) {
        this->instance = new Network();
    }

    return this->instance;
}

int Network::server_open(int port)
{
    struct sockaddr_in serv_addr;

    if ((this->server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("[Network] Couldn't create socket: ");
        return -1;
    }
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    if (bind(this->server_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("[Network] Couldn't bind socket: ");
        return -1;
    }

    if (listen(this->server_sock, 10) < 0) {
        perror("[Network] Couldn't listen on socket: ");
        return -1;
    }

    return 0;
}

int Network::server_accept(void)
{
    int sock;

    if ((sock = accept(this->server_sock, (struct sockaddr *)NULL, NULL)) < 0) {
        perror("[Network] Couldn't connect to the server: ");
        return -1;
    }
    return sock;
}

int Network::client_connect(char *server_address, int port)
{
    struct sockaddr_in serv_addr;

    //Connect to the server listening socket
    if ((this->server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("[Network] Error creating socket: ");
        return -1;
    }
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, server_address, &serv_addr.sin_addr) <= 0) {
        perror("[Network] inet_pton error: ");
        return -1;
    }
    if (connect(this->server_sock, (struct sockaddr *)&serv_addr,
                sizeof(serv_addr)) < 0)
    {
        perror("[Network] Couldn't connect to the server: ");
        return -1;
    }

    return 0;
}

int Network::wait(net_req_t req_type)
{
    return 0;
}

int Network::forward(Scheduling *scheduling)
{
    return 0;
}

int Network::bcast(Scheduling *scheduling)
{
    return 0;
}
