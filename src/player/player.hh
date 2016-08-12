#ifndef PLAYER_HH_
# define PLAYER_HH_

class Room;

class Player {
public:
    Player(void);
    ~Player(void);

    Room *getRoom(void) { return this->room; };
    void setRoom(Room *room) { this->room = room; };

protected:
    Room *room;
};

#include "room/room.hh"

#endif /* !PLAYER_HH_ */
