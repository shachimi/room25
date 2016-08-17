#ifndef AVATAR_HH_
# define AVATAR_HH_

class Room;

class Avatar {
public:
    Avatar(void);
    ~Avatar(void);

    /* {{{ Getters and setters */

public:
    Room *getRoom(void) const { return this->room; };
    void setRoom(Room *room) { this->room = room; };

    /* }}} */

protected:
    Room *room;
};

# include "room/room.hh"

#endif /* !AVATAR_HH_ */
