#ifndef SCHEDULING_HH_
# define SCHEDULING_HH_

# include "game/enum.hh"
# include "network/enum.hh"

class Player;

class Scheduling {
public:
    Scheduling(void);
    ~Scheduling(void);

    bool isValid(void);

    /* {{{ Getters and Setter */

public:
    action_t getAction(int turn);
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
    int getAction1(void) const { return this->action_1; };
    int getAction2(void) const { return this->action_2; };

    /* }}} */

    net_scheduling_t toNetScheduling(void);


private:
    bool adrenaline;
    action_t action_1;
    action_t action_2;
    Player *owner; /* TODO: replace by Avatar at term */
};

# include "player/player.hh"

#endif /* !SCHEDULING_HH_ */
