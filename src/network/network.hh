#ifndef NETWORK_HH_
# define NETWORK_HH_

# include "network/enum.hh"
# include "game/scheduling.hh"
# include "network/message-factory.hh"
# include "network/message.hh"

// Static singleton class
class Network {
public:
    // Initialisation of the socket
    int server_open(int port);
    int server_accept(void);
    int client_connect(char *server_address, int port);

    //Client side
    Message *wait(net_req_t req_type = REQ_NONE);
    int forward(Message *message);

    //Server side
    int tell(Message *message, int sock);

    // Singleton
    Network *getInstance(void);

private:
    net_msg_t recv_msg(int sock);
    int send_msg(net_msg_t msg, int sock);

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
