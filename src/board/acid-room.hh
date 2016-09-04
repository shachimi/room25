#ifndef ACID_ROOM_HH_
# define ACID_ROOM_HH_

# include "board/room_effect.hh"
# include "player/player.hh"

class AcidRoom : public RoomEffect {
public:
    AcidRoom(void);
    ~AcidRoom(void);
    virtual void prisoner_enter(Avatar *prisoner);
};

#endif /* !ACID_ROOM_HH_ */
