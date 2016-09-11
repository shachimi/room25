#ifndef GAME_CLIENT_HH_
# define GAME_CLIENT_HH_

# include <queue>

# include "game/game.hh"
# include "player/player.hh"
# include "board/board.hh"
# include "game/rule.hh"
# include "player/prisoner.hh"


class GameClient : public Game {
public:
    int init_game(Rule *rule, char *server_address = "127.0.0.1",
                  int port = 5000);
    virtual void play_turn(void);

    int recv();

protected:
    int sock_fd;
};

#endif /* !GAME_CLIENT_HH_ */
