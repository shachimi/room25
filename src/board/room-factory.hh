#ifndef ROOM_FACTORY_HH_
# define ROOM_FACTORY_HH_

# include "board/room.hh"

class RoomFactory {
public:
    static Room *getDeadlyRoom(void);
    static Room *getAcidRoom(void);
    static Room *getFloodingRoom(void);
    static Room *getTortureRoom(void);
    static Room *getGearRoom(void);
    static Room *getVisionRoom(void);
    static Room *getIllusionRoom(void);
    static Room *getWarpRoom(void);
    static Room *getSafeRoom(void);

private: /* Should never be instanciated */
    RoomFactory() {};
    ~RoomFactory() {};
};

#endif /* !ROOM_FACTORY_HH_ */




