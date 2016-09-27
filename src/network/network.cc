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
#include <assert.h>

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

net_msg_t Network::recv_msg(int sock)
{
    int code;
    net_msg_t msg;

    assert(sock >= 0);
    if ((code = read(sock, &msg, sizeof(msg))) < 0) {
        perror("[Network] failed to recv msg: ");
        msg.req = REQ_ERROR_READ;
    } else if (code == 0) {
        perror("[Network] connection lost: ");
        msg.req = REQ_ERROR_DISCONNECT;
    }
    return msg;
}

int Network::send_msg(net_msg_t msg, int sock)
{
    int code;

    assert(sock >= 0);
    if ((code = write(sock, &msg, sizeof(msg))) < 0) {
        perror("[Network] failed to send msg: ");
    } else if (code == 0) {
        perror("[Network] connection lost: ");
    }
    return code;
}

Message *Network::wait(net_req_t req_type)
{
    net_msg_t msg;
    int req_ok = 0;

    do {
        msg = recv_msg(this->server_sock);
        if (req_type == REQ_NONE || msg.req == req_type) {
            // We have received the expected message
            // Handle it
            req_ok = 1;
        } else {
            // Log error for the recvd msg
        }
    } while (!req_ok);
    return MessageFactory::getMessageFromNet(&msg);
}

int Network::forward(Message *message)
{
    net_msg_t msg;

    msg = message->to_net_msg();
    msg.req = REQ_SET_SCHEDULING;

    return send_msg(msg, this->server_sock);
}

Message *Network::wait(net_req_t req_type, int sock)
{
    net_msg_t msg;
    int req_ok = 0;

    if (!sock) {
        sock = this->server_sock;
    }

    do {
        msg = recv_msg(sock);
        if (req_type == REQ_NONE || msg.req == req_type) {
            // We have received the expected message
            // Handle it
            req_ok = 1;
        } else {
            // Log error for the recvd msg
        }
    } while (!req_ok);
    return MessageFactory::getMessageFromNet(&msg);
}

int Network::tell(Message *message, int sock)
{
    net_msg_t msg;

    msg = message->to_net_msg();
    msg.req = REQ_SET_SCHEDULING;

    return send_msg(msg, sock);
}
