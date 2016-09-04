#ifndef FLOODING_ROOM_HH_
# define FLOODING_ROOM_HH_

# include "board/room_effect.hh"
# include "board/room_effect.hh"

class FloodingRoom : public RoomEffect {
public:
    FloodingRoom(void);
    ~FloodingRoom(void);
    virtual void prisoner_enter(Avatar *prisoner, Cell *from);
    virtual void turn_ends(void);

private:
    int flooded_cpt;
};

#endif /* !FLOODING_ROOM_HH_ */
