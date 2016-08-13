#ifndef SLIDE_HH_
# define SLIDE_HH_

# include "game/action.hh"

class Slide : public Action {
public:
    Slide(void);
    ~Slide(void);

    virtual void exec(void);
};

#endif /* !SLIDE_HH_ */
