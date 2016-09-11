#ifndef PLAYER_HH_
# define PLAYER_HH_

# include <vector>
# include "game/enum.hh"
# include "player/avatar.hh"
# include "board/cell.hh"

class Room;
class Scheduling;

class Player {
public:
    Player(int id);
    ~Player(void);

    /* Game mechanics */
    /* {{{ Actions */

    virtual Scheduling *getScheduling(void) = 0;
    virtual bool useAction(void) = 0;
    virtual direction_t selectMove(int allowed_dir) = 0;
    virtual direction_t selectSlide(int allowed_dir) = 0;
    virtual direction_t selectSee(int allowed_dir) = 0;
    virtual direction_t selectPushDirection(int allowed_dir) = 0;
    virtual Cell* selectCell(std::vector<Cell *> allowed_cells) { return NULL; };
    /* TODO: distinguish complex avatar from player one */
    virtual Avatar *selectPushTarget(std::vector<Avatar *> players) = 0;

    virtual bool goOutComplex(void) { return true; };

    /* }}} */
    /* {{{ Captor */

    virtual void seeRoom(const Room *room) = 0;

    /* }}} */
    /* {{{ Getters and setters */

public:
    int getId(void) { return this->id; };
    int getActionsStock(void) const { return this->actions_stock; };
    void setActionsStock(action_t action) { this->actions_stock |= action; };
    Avatar *getAvatar(void) const { return this->avatar; };
    void setAvatar(Avatar *avatar) { this->avatar = avatar; };
    /* TODO: prepare to handle several avatar */
    Room *getAvatarRoom(void) { return this->avatar ? this->avatar->getRoom() : NULL; };
    bool isAvatarAlive(void);

    /* }}} */

protected:
    int id;
    int actions_stock; /* mask of action_t */
    Avatar *avatar;
};

#include "board/room.hh"
#include "game/scheduling.hh"

#endif /* !PLAYER_HH_ */
