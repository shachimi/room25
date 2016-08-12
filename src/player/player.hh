#ifndef PLAYER_HH_
# define PLAYER_HH_

# include "game/enum.hh"

class Room;

class Player {
public:
    Player(void);
    ~Player(void);

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

#endif /* !PLAYER_HH_ */
