#ifndef TORTURE_ROOM_HH_
# define TORTURE_ROOM_HH_

# include "board/room_effect.hh"
# include "player/player.hh"

class TortureRoom : public RoomEffect {
public:
    TortureRoom(void);
    ~TortureRoom(void);
    virtual void prisoner_stay(Avatar *prisoner);
};

#endif /* !TORTURE_ROOM_HH_ */
