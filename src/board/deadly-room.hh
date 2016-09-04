#ifndef DEADLY_ROOM_HH_
# define DEADLY_ROOM_HH_

# include "board/room_effect.hh"
# include "room_effect.hh"

class DeadlyRoom : public RoomEffect {
public:
    DeadlyRoom(void);
    ~DeadlyRoom(void);
    virtual void prisoner_enter(Avatar *prisoner, Cell *from);
};

#endif /* !DEADLY_ROOM_HH_ */
