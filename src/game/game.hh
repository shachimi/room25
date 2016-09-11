#ifndef GAME_HH_
# define GAME_HH_

# include <queue>

# include "player/player.hh"
# include "board/board.hh"
# include "game/rule.hh"
# include "player/prisoner.hh"


class Game {
public:
    static Game *getInstance(void);

    void init_game(Rule *rule, int nb_players, int nb_turn);
    void play_turn(void);
    void exec(action_t action, Player *player);
    void execMove(Player *player);
    void execSlide(Player *player);
    void execPush(Player *player);
    void execSee(Player *player);

    void rotatePlayer(void);
    void removeAvatar(Avatar *avatar);
    void addPlayer(Player *player);

    bool checkWin(int pos, direction_t dir);

    /* Getter and setters */
    std::vector<Player *> getPlayers(void) { return this->players; };
    void setPlayers(std::vector<Player *> players) { this->players = players; };
    Board *getBoard(void) { return this->board; };
    void setBoard(Board *board) { this->board = board; };
    Rule *getRule(void) { return this->rule; };
    void setRule(Rule *rule) { this->rule = rule; };

protected:
    void ends_turn(void);

protected:
    /* TODO: made a Rule class to abstract win/lose/play_turn method */
    std::vector<Player *> players;
    Board *board;

    Rule *rule;
    int first_player;

private:
    Game(void);
    ~Game(void);
    static Game *instance;
};

#endif /* !GAME_HH_ */
