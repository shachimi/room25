#ifndef ILLUSION_ROOM_HH_
# define ILLUSION_ROOM_HH_

# include "board/room_effect.hh"
# include "player/player.hh"
# include "player/prisoner.hh"
#include "game/game.hh"
#include "board/cell.hh"

#include "utils/Log.hh"

class IllusionRoom : public RoomEffect {
public:
    IllusionRoom(void);
    ~IllusionRoom(void);
    virtual void prisoner_enter(Avatar *prisoner, Cell *from);
};

#endif /* !ILLUSION_ROOM_HH_ */
