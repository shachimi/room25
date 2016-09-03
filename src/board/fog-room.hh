#ifndef FOG_ROOM_HH_
# define FOG_ROOM_HH_

# include "room_effect.hh"

class FogRoom : public RoomEffect {
public:
    FogRoom(void);
    ~FogRoom(void);

    virtual int validateDirection(int directions, action_t action);
};

#endif /* !FOG_ROOM_HH_ */
