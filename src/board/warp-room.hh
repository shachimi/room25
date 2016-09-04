#ifndef WARP_ROOM_HH_
# define WARP_ROOM_HH_

# include "board/room_effect.hh"
# include "player/player.hh"
# include "player/prisoner.hh"
#include "game/game.hh"
#include "board/cell.hh"

#include "utils/Log.hh"

class WarpRoom : public RoomEffect {
public:
    WarpRoom(void);
    ~WarpRoom(void);
    virtual void prisoner_enter(Avatar *prisoner, Cell *from);
};

#endif /* !WARP_ROOM_HH_ */
