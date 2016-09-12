#ifndef GAME_CLIENT_HH_
# define GAME_CLIENT_HH_

# include <queue>

# include "game/game.hh"
# include "player/player.hh"
# include "board/board.hh"
# include "game/rule.hh"
#include "network/enum.hh"

class GameClient : public Game {
public:
    static Game *getInstance(void);
    int init_game(Rule *rule, char *server_address = "127.0.0.1",
                  int port = 5000);
    virtual void play_turn(void);

protected:
    GameClient(void);
    ~GameClient(void);

    int recv_msg();
    int send(net_msg_t msg);

protected:
    int sock_fd;
};

#endif /* !GAME_CLIENT_HH_ */
