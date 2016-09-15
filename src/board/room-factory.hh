#ifndef ROOM_FACTORY_HH_
# define ROOM_FACTORY_HH_

# include "board/room.hh"
# include "board/enum.hh"

class RoomFactory {
public:
    static Room *getDeadlyRoom(void);
    static Room *getAcidRoom(void);
    static Room *getFloodingRoom(void);
    static Room *getTortureRoom(void);
    static Room *getIllusionRoom(void);

    static Room *getFreezeRoom(void);
    static Room *getPrisonRoom(void);
    static Room *getFogRoom(void);
    static Room *getVortexRoom(void);
    static Room *getPivotRoom(void);

    static Room *getCenterRoom(void);
    static Room *getExitRoom(void);
    static Room *getGearRoom(void);
    static Room *getVisionRoom(void);
    static Room *getWarpRoom(void);
    static Room *getSafeRoom(void);
    static Room *getTunnelRoom(void);

    static Room *getRoom(effect_t effect);

private: /* Should never be instanciated */
    RoomFactory() {};
    ~RoomFactory() {};
};

#endif /* !ROOM_FACTORY_HH_ */




