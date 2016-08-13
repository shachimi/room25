#ifndef PUSH_HH_
# define PUSH_HH_

# include "game/action.hh"

class Push : public Action {
public:
    Push(void);
    ~Push(void);

    virtual void exec(void);
};

#endif /* !PUSH_HH_ */
