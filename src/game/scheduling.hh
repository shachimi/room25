#ifndef SCHEDULING_HH_
# define SCHEDULING_HH_

# include "game/enum.hh"
# include "player/player.hh"

class Scheduling {
public:
    Scheduling(void);
    ~Scheduling(void);

    /* {{{ Getters and Setter */

public:
    action_t getAction(int turn) const;
    void setAction(action_t action, int turn) {
        if (turn == 1) {
            this->action_1 = action;
        } else {
            this->action_2 = action;
        }
    };
    Player *getOwner(void) const { return this->owner; };
    void setOwner(Player *owner) { this->owner = owner; };
    bool getAdrenaline(void) const { return this->adrenaline; };
    void setAdrenaline(bool adrenaline) { this->adrenaline = adrenaline; };

    /* }}} */


private:
    bool adrenaline;
    action_t action_1;
    action_t action_2;
    Player *owner;
};

#endif /* !SCHEDULING_HH_ */
