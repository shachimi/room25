#ifndef GAME_HH_
# define GAME_HH_

class Game {
public:
    Game(void);
    ~Game(void);
    void play_turn(void);
    void exec(Action * action);

    void rotatePlayer(void);

    /* Getter and setters */
    std::vector<Player *> getPlayers(void) { return this->players; };
    void setPlayers(std::vector<Player *> players) { this->players = players; };

protected:
    std::queue<Player *> players;
};

#endif /* !GAME_HH_ */
