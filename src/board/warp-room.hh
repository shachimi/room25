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
    virtual void prisoner_enter(Avatar *prisoner);
    virtual void turn_starts(void);
    virtual void prisoner_stay(Avatar *prisoner);
    virtual void turn_ends(void);
};

#endif /* !WARP_ROOM_HH_ */
