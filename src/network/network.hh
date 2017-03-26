#ifndef NETWORK_HH_
# define NETWORK_HH_

# include <sys/socket.h>
# include <stdio.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <assert.h>
# include <string.h>

# include "enum.hh"

class Network {
public:
    // Connection
    virtual int connect(const int port) = 0;

    // Communication
    int send(const net_msg_t& msg, int sock = -1);
    net_msg_t recv(int sock = -1);

protected:
    int getSock(int sock = -1, bool must_be_connected = false);

protected:
    int sock;

protected:
    Network();
    virtual ~Network() { };
};

#endif /* NETWORK_HH_ */






