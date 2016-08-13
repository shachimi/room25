#ifndef SEE_HH_
# define SEE_HH_

# include "game/action.hh"

class See : public Action {
public:
    See(void);
    ~See(void);

    virtual void exec(void);
};

#endif /* !SEE_HH_ */
