#ifndef STANDARD_RULE_HH_
# define STANDARD_RULE_HH_

# include "game/rule.hh"

class StandardRule : public Rule {
public:
    StandardRule(void);
    ~StandardRule(void);

    virtual Board *init_board(void);
    virtual Board *init_board(std::vector<Room *> rooms);
    /** Method to manage a game. */
    virtual bool manage_game(void);
    /** Workflow to destroy a prisoner.
     *
     *  Return false if the game continue, true if it is GameOver.
     */
    virtual bool destroyPrisoner(Prisoner *prisoner);
};

#endif /* !STANDARD_RULE_HH_ */
