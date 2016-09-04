#ifndef TUNNEL_ROOM_HH_
# define TUNNEL_ROOM_HH_

# include "board/room_effect.hh"

class Cell;

class TunnelRoom : public RoomEffect {
public:
    TunnelRoom(void);
    ~TunnelRoom(void);
    virtual void prisoner_enter(Avatar *prisoner);
};

#include "board/cell.hh"

#endif /* !TUNNEL_ROOM_HH_ */
