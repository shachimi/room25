#ifndef PLAYER_HH_
# define PLAYER_HH_

# include <vector>
# include "game/enum.hh"

class Room;
class Action;

class Player {
public:
    Player(void);
    ~Player(void);

    /* Game mechanics */
    /* {{{ Actions */

    virtual Action *getAction(void) = 0;
    virtual direction_t selectMove(int allowed_dir) = 0;
    virtual direction_t selectSlide(int allowed_dir) = 0;
    virtual direction_t selectSee(int allowed_dir) = 0;
    virtual direction_t selectPushDirection(int allowed_dir) = 0;
    virtual Player *selectPushTarget(std::vector<Player *> players) = 0;

    /* }}} */
    /* {{{ captor */

    virtual void seeRoom(const Room *room) = 0;

    /* }}} */

public:
    /* Getters and setters */
    Room *getRoom(void) const { return this->room; };
    void setRoom(Room *room) { this->room = room; };
    int getActionsStock(void) const { return this->actions_stock; };
    int setActionsStock(action_t action) { this->actions_stock |= action; };


protected:
    Room *room;
    int  actions_stock; /* mask of action_t */
};

#include "room/room.hh"
#include "game/action.hh"

#endif /* !PLAYER_HH_ */
