#ifndef SERVER_HH_
# define SERVER_HH_

# include <iostream>
# include <map>

# include "game/game.hh"
# include "board/room.hh"

class Server {
public:
    Server(void);
    ~Server(void);

    int start(void);
    int close(void);

    void send(Player *player, Room *room);

    void bcast(Room *room);

    /* Getter and setters */

protected:
    int run(void);

protected:
    int port;
    int listenfd;
    struct sockaddr_in address;
    std::map<NetworkTermPlayer*, std::thread> clients;
};

#endif /* !SERVER_HH_ */
