#ifndef PRISONER_HH_
# define PRISONER_HH_

# include "player/avatar.hh"
# include "player/player.hh"

class Prisoner : public Avatar {
public:
    Prisoner(Player *player);
    ~Prisoner(void);

    virtual void doSpecialMove(void){}/* = 0 */;
    virtual void destroy(void);

    /* {{{ Getters and setters */

    Player *getOwner(void) { return this->owner; };

    bool isAlive(void) const { return this->is_alive; };
private:
    void setIsAlive(bool is_alive) { this->is_alive = is_alive; };

    /* }}} */

protected:
    bool is_alive;
    Player *owner;
};


#endif /* !PRISONER_HH_ */
