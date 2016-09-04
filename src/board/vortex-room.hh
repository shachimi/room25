#ifndef VORTEX_ROOM_HH_
# define VORTEX_ROOM_HH_

# include "room_effect.hh"

class VortexRoom : public RoomEffect {
public:
    VortexRoom(void);
    ~VortexRoom(void);
    virtual void prisoner_enter(Avatar *prisoner, Cell *from);
};

#endif /* !VORTEX_ROOM_HH_ */
