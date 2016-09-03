#ifndef RULE_HH_
# define RULE_HH_

# include "board/room_effect.hh"
# include "player/prisoner.hh"

class Rule {
public:
    Rule(void);
    ~Rule(void);
    virtual Board *init_board(std::vector<RoomEffect *> rooms) = 0;
    /** Workflow to destroy a prisoner.
     *
     *  Return false if the game continue, true if it is GameOver.
     */
    virtual bool destroyPrisoner(Prisoner *prisoner) = 0;
    /* TODO: the win condition will be by knowing if we can go out during
     *       a slide
     */

public:
    int getTurn(void) { return this->turn; };
    void setTurn(int turn) { this->turn = turn; };

private:
    int turn;
};

#endif /* !RULE_HH_ */