#ifndef FREEZE_ROOM_HH_
# define FREEZE_ROOM_HH_

# include "room_effect.hh"

class FreezeRoom : public RoomEffect {
public:
    FreezeRoom(void);
    ~FreezeRoom(void);

    virtual bool validateSchedule(Scheduling *scheduling);
};

#endif /* !FREEZE_ROOM_HH_ */
