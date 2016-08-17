#ifndef PLAYER_HH_
# define PLAYER_HH_

# include <vector>
# include "game/enum.hh"
# include "player/avatar.hh"

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
    /* TODO: distinguish complex avatar from player one */
    virtual Avatar *selectPushTarget(std::vector<Avatar *> players) = 0;

    /* }}} */
    /* {{{ Captor */

    virtual void seeRoom(const Room *room) = 0;

    /* }}} */
    /* {{{ Getters and setters */

public:
    int getActionsStock(void) const { return this->actions_stock; };
    int setActionsStock(action_t action) { this->actions_stock |= action; };
    Avatar *getAvatar(void) const { return this->avatar; };
    void setAvatar(Avatar *avatar) { this->avatar = avatar; };

    /* }}} */

protected:
    int  actions_stock; /* mask of action_t */
    Avatar *avatar;
};

#include "room/room.hh"
#include "game/action.hh"

#endif /* !PLAYER_HH_ */
