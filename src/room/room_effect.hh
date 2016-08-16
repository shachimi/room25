#ifndef ROOM_EFFECT_HH_
# define ROOM_EFFECT_HH_

# include <iostream>
# include <vector>

enum room_kind_t {
    ROOM_KIND_CENTER,
    ROOM_KIND_EXIT,
    ROOM_KIND_SAFE,
    ROOM_KIND_OBS,
    ROOM_KIND_DANGER,
};

class Player;
class Room;

class RoomEffect {
public:
    RoomEffect(void);
    RoomEffect(room_kind_t kind);
    ~RoomEffect(void);
    /** The prisoner is already inside the room when the method is called. */
    virtual void prisoner_enter(Player * prisoner);
    virtual void turn_starts(void);
    virtual void prisoner_stay(Player * prisoner);
    virtual void turn_ends(void);

    virtual void print(std::ostream& out);

    /* Getter and setters */
    void setKind(room_kind_t kind) { this->kind = kind; };
    void setRoom(Room *room) { this->room = room; };

protected:
    room_kind_t kind;
    Room *room;
};

# include "player/player.hh"
# include "room/room.hh"

#endif /* !ROOM_EFFECT_HH_ */
