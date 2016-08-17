#ifndef DEADLY_ROOM_HH_
# define DEADLY_ROOM_HH_

# include "room_effect.hh"

class DeadlyRoom : public RoomEffect {
public:
    DeadlyRoom(void);
    ~DeadlyRoom(void);
    virtual void prisoner_enter(Avatar *prisoner);
    virtual void turn_starts(void);
    virtual void prisoner_stay(Avatar *prisoner);
    virtual void turn_ends(void);
};

#endif /* !DEADLY_ROOM_HH_ */
