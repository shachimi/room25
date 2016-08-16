#ifndef ACID_ROOM_HH_
# define ACID_ROOM_HH_

# include "player/player.hh"

class AcidRoom : public RoomEffect {
public:
    AcidRoom(void);
    ~AcidRoom(void);
    virtual void prisoner_enter(Player *prisoner);
    virtual void turn_starts(void);
    virtual void prisoner_stay(Player *prisoner);
    virtual void turn_ends(void);
};

#endif /* !ACID_ROOM_HH_ */
