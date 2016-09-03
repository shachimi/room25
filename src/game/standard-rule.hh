#ifndef STANDARD_RULE_HH_
# define STANDARD_RULE_HH_

# include "game/rule.hh"

class StandardRule {
public:
    StandardRule(void);
    ~StandardRule(void);

    virtual Board *init_board(std::vector<RoomEffect *> rooms);
    /** Workflow to destroy a prisoner.
     *
     *  Return false if the game continue, true if it is GameOver.
     */
    virtual bool destroyPrisoner(Prisoner *prisoner);
};

#endif /* !STANDARD_RULE_HH_ */
