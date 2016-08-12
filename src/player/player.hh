#ifndef PLAYER_HH_
# define PLAYER_HH_

# include "game/enum.hh"

class Room;
class Action;

class Player {
public:
    Player(void);
    ~Player(void);

    /* Game mechanics */
    virtual Action *getAction(void) = 0;
    virtual direction_t execMove(int allowed_dir) = 0;

    /* Getters and setters */
    Room *getRoom(void) { return this->room; };
    void setRoom(Room *room) { this->room = room; };
    int getActionsStock(void) { return this->actions_stock; };
    int setActionsStock(action_t action) { this->actions_stock |= action; };


protected:
    Room *room;
    int  actions_stock; /* mask of action_t */
};

#include "room/room.hh"
#include "game/action.hh"

#endif /* !PLAYER_HH_ */
