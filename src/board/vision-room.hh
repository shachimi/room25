#ifndef VISION_ROOM_HH_
# define VISION_ROOM_HH_

# include "board/room_effect.hh"
# include "player/player.hh"
# include "player/prisoner.hh"
#include "game/game.hh"
#include "board/cell.hh"

#include "utils/Log.hh"

class VisionRoom : public RoomEffect {
public:
    VisionRoom(void);
    ~VisionRoom(void);
    virtual void prisoner_enter(Avatar *prisoner, Cell *from);
};

#endif /* !VISION_ROOM_HH_ */
