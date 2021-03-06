#ifndef AVATAR_HH_
# define AVATAR_HH_

class Room;

class Avatar {
public:
    Avatar(void);
    ~Avatar(void);

    virtual void destroy(void) = 0;

    /* {{{ Getters and setters */

public:
    Room *getRoom(void) const { return this->room; };
    void setRoom(Room *room) { this->room = room; };

    /* }}} */

protected:
    Room *room;
};

# include "board/room.hh"

#endif /* !AVATAR_HH_ */
