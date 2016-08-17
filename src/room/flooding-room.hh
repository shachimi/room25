#ifndef FLOODING_ROOM_HH_
# define FLOODING_ROOM_HH_

# include "room/room_effect.hh"

class FloodingRoom : public RoomEffect {
public:
    FloodingRoom(void);
    ~FloodingRoom(void);
    virtual void prisoner_enter(Avatar *prisoner);
    virtual void turn_starts(void);
    virtual void prisoner_stay(Avatar *prisoner);
    virtual void turn_ends(void);

private:
    int flooded_cpt;
};

#endif /* !FLOODING_ROOM_HH_ */
