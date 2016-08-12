#ifndef HUMAN_PLAYER_HH_
# define HUMAN_PLAYER_HH_

# include "player.hh"

class HumanPlayer : Player {
public:
    virtual Action *getAction(void);
    virtual direction_t execMove(int allowed_dir);

};


#endif /* !HUMAN_PLAYER_HH_ */
