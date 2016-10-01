#ifndef GAME_SERVER_HH_
# define GAME_SERVER_HH_

# include <queue>

# include "game/game.hh"
# include "player/player.hh"
# include "board/board.hh"
# include "game/rule.hh"
#include "network/enum.hh"

class GameServer : public Game {
public:
    static Game *getInstance(void);
    int init_game(Rule *rule, int nb_clients, int nb_turn,
                  char *server_address = "127.0.0.1",
                  int port = 5000);
    virtual void play_turn(void);

protected:
    std::vector<int> clients;

protected:
    GameServer(void);
    ~GameServer(void);
};

#endif /* !GAME_SERVER_HH_ */
