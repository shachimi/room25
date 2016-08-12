#ifndef ACTION_HH_
# define ACTION_HH_

# include "player/player.hh"

class Action {
public:
    Action(void);
    ~Action(void);

    virtual void exec(void) = 0;

    /* Getters and setters */
    Player *getOwner(void) { return this->owner; };
    void setOwner(Player *owner) { this->owner = owner; };

protected:
    Player *owner;
};


#endif /* !ACTION_HH_ */
