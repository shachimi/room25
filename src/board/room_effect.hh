#ifndef ROOM_EFFECT_HH_
# define ROOM_EFFECT_HH_

# include <iostream>
# include <vector>

# include "game/scheduling.hh"
# include "game/enum.hh"

class Avatar;
class Room;

class RoomEffect {
public:
    RoomEffect(void);
    RoomEffect(room_kind_t kind);
    ~RoomEffect(void);
    /** The prisoner is already inside the room when the method is called. */
    virtual void turn_starts(void) {};
    virtual void prisoner_enter(Avatar *prisoner, Cell *from) {};
    virtual void prisoner_stay(Avatar *prisoner) {};
    virtual void prisoner_leave(Avatar *prisoner) {};
    virtual bool validateSchedule(Scheduling *scheduling) { return true; };
    virtual int validateDirection(int directions, action_t action) {
        return directions;
    };

    virtual void turn_ends(void) {};

    virtual bool is_accessible(Avatar *avatar) { return this->room->isAccessible(); };
    virtual void print(std::ostream& out);

    /* Getter and setters */
    room_kind_t getKind(void) { return this->kind; };
    void setKind(room_kind_t kind) { this->kind = kind; };
    void setRoom(Room *room) { this->room = room; };

protected:
    room_kind_t kind;
    Room *room;
};

# include "player/avatar.hh"
# include "board/room.hh"

#endif /* !ROOM_EFFECT_HH_ */
