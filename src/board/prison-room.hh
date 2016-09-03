#ifndef PRISON_ROOM_HH_
# define PRISON_ROOM_HH_

# include "room_effect.hh"

class PrisonRoom : public RoomEffect {
public:
    PrisonRoom(void);
    ~PrisonRoom(void);

    virtual int validateDirection(int directions, action_t action);
};

#endif /* !PRISON_ROOM_HH_ */
