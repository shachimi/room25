#include "network.hh"

Network::Network()
    : sock(0)
{
}

int Network::getSock(int sock, bool must_be_connected) {
    if (sock < 0) {
        sock = this->sock;
    }

    if (must_be_connected) {
        assert(sock >= 0);
    }

    return sock;
}

int Network::send(const net_msg_t &msg, int sock)
{
    int code;

    sock = getSock(sock, true);
    if ((code = write(sock, &msg, sizeof(msg)) < 0)) {
        perror("[Network] failed to send msg");
    }

    return code;
}

net_msg_t Network::recv(int sock)
{
    int code;
    net_msg_t msg;

    sock = getSock(sock, true);
    if ((code = read(sock, &msg, sizeof(msg)) < 0)) {
        perror("[Network] failed to recv msg");
    } else
    if (code == 0) {
        perror("[Network] connection lost");
    }

    return msg;
}
