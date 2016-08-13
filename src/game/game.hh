#ifndef GAME_HH_
# define GAME_HH_

# include <queue>

# include "player/player.hh"
# include "room/board.hh"
# include "game/action.hh"
# include "game/move.hh"
# include "game/push.hh"
# include "game/slide.hh"
# include "game/see.hh"


class Game {
public:
    static Game *getInstance(void);

    void play_turn(void);
    void exec(Action *action);
    void exec(Move *move);
    void exec(Slide *slide);
    void exec(Push *slide);
    void exec(See *see);

    void rotatePlayer(void);

    /* Getter and setters */
    std::queue<Player *> getPlayers(void) { return this->players; };
    void setPlayers(std::queue<Player *> players) { this->players = players; };
    Board *getBoard(void) { return this->board; };
    void setBoard(Board *board) { this->board = board; };

private:


protected:
    std::queue<Player *> players;
    Board *board;

private:
    Game(void);
    ~Game(void);
    static Game *instance;
};

#endif /* !GAME_HH_ */
