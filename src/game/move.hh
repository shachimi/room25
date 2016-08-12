#ifndef MOVE_HH_
# define MOVE_HH_

# include "game/action.hh"

class Move : public Action {
public:
    Move(void);
    ~Move(void);

    virtual void exec(void);
};

#endif /* !MOVE_HH_ */
