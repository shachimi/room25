#ifndef NETWORK_HH_
# define NETWORK_HH_

# include "network/enum.hh"
# include "game/scheduling.hh"

// Static singleton class
class Network {
public:
    // Initialisation of the socket
    int server_open(int port);
    int server_accept(void);
    int client_connect(char *server_address, int port);

    int wait(net_req_t req_type);

    int forward(Scheduling *scheduling);
    // TODO same with action

    int bcast(Scheduling *scheduling);
    // TODO same with action

    // Singleton
    Network *getInstance(void);

private:
    int server_sock;

private:
    // This class is a singleton so we don't want to be able to instantiate it
    // manually
    Network(void);
    ~Network(void);

    static Network *instance;
};

# include "player/avatar.hh"
# include "board/room.hh"

#endif /* !NETWORK_HH_ */
