#ifndef ROOM_EFFECT_HH_
# define ROOM_EFFECT_HH_

# include <iostream>
# include <vector>

# include "player/player.hh"

enum room_kind_t {
    ROOM_KIND_CENTER,
    ROOM_KIND_EXIT,
    ROOM_KIND_SAFE,
    ROOM_KIND_OBS,
    ROOM_KIND_DANGER,
};

class RoomEffect {
public:
    RoomEffect(void);
    ~RoomEffect(void);
    virtual void prisoner_enter(Player * prisoner);
    virtual void turn_starts(void);
    virtual void prisoner_stay(Player * prisoner);
    virtual void turn_ends(void);

    virtual void print(std::ostream& out);

    /* Getter and setters */
    void setKind(room_kind_t kind) { this->kind = kind; };

protected:
    room_kind_t kind;
};

#endif /* !ROOM_EFFECT_HH_ */
