#ifndef ROOM_EFFECT_HH_
# define ROOM_EFFECT_HH_

# include <iostream>
# include <vector>

# include "game/scheduling.hh"

enum room_kind_t {
    ROOM_KIND_CENTER,
    ROOM_KIND_EXIT,
    ROOM_KIND_SAFE,
    ROOM_KIND_OBS,
    ROOM_KIND_DANGER,
};

class Avatar;
class Room;

class RoomEffect {
public:
    RoomEffect(void);
    RoomEffect(room_kind_t kind);
    ~RoomEffect(void);
    /** The prisoner is already inside the room when the method is called. */
    virtual void turn_starts(void);
    virtual void prisoner_enter(Avatar *prisoner);
    virtual void prisoner_stay(Avatar *prisoner);
    /* TODO: take action + avatar instead */
    virtual bool validateSchedule(Scheduling *scheduling);
    virtual void turn_ends(void);

    virtual bool is_accessible(Avatar *avatar) { return true; };
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
