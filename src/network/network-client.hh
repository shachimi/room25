#ifndef NETWORK_CLIENT_HH_
# define NETWORK_CLIENT_HH_

#include "network/network.hh"

class NetworkClient : public Network {
public:
    NetworkClient();
    ~NetworkClient();

    // Connection
    int connect(const int port);
    int connect(const int port, const char *address);
};

#endif
