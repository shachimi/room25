#ifndef ROOM_FACTORY_HH_
# define ROOM_FACTORY_HH_

# include "board/room.hh"

class RoomFactory {
public:
    Room *getDeadlyRoom(void);
    Room *getAcidRoom(void);
    Room *getFloodingRoom(void);
    Room *getTortureRoom(void);

private: /* Should never be instanciated */
    RoomFactory() {};
    ~RoomFactory() {};
};

#endif /* !ROOM_FACTORY_HH_ */




