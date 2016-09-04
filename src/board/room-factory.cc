#include "board/freeze-room.hh"
#include "board/prison-room.hh"
#include "board/vortex-room.hh"
#include "board/pivot-room.hh"
#include "board/fog-room.hh"
#include "board/flooding-room.hh"
#include "board/deadly-room.hh"
#include "board/acid-room.hh"
#include "board/torture-room.hh"
#include "board/room-factory.hh"
#include "board/gear-room.hh"
#include "board/vision-room.hh"
#include "board/illusion-room.hh"
#include "board/warp-room.hh"

/* {{{ Danger room */

Room *RoomFactory::getDeadlyRoom(void)
{
    Room *room = new Room();
    RoomEffect *effect = new DeadlyRoom();

    room->setEffect(effect);
    return room;
}

Room *RoomFactory::getAcidRoom(void)
{
    Room *room = new Room();
    RoomEffect *effect = new AcidRoom();

    room->setEffect(effect);
    return room;
}

Room *RoomFactory::getFloodingRoom(void)
{
    Room *room = new Room();
    RoomEffect *effect = new FloodingRoom();

    room->setEffect(effect);
    return room;
}

Room *RoomFactory::getTortureRoom(void)
{
    Room *room = new Room();
    RoomEffect *effect = new TortureRoom();

    room->setEffect(effect);
    return room;
}

Room *RoomFactory::getIllusionRoom(void)
{
    Room *room = new Room();
    RoomEffect *effect = new IllusionRoom();

    room->setEffect(effect);
    return room;
}

/* }}} */
/* {{{ Obstacle room */

Room *RoomFactory::getFreezeRoom(void)
{
    Room *room = new Room();
    RoomEffect *effect = new FreezeRoom();

    room->setEffect(effect);
    return room;
}

Room *RoomFactory::getFogRoom(void)
{
    Room *room = new Room();
    RoomEffect *effect = new FogRoom();

    room->setEffect(effect);
    return room;
}

Room *RoomFactory::getPrisonRoom(void)
{
    Room *room = new Room();
    RoomEffect *effect = new PrisonRoom();

    room->setEffect(effect);
    return room;
}

Room *RoomFactory::getVortexRoom(void)
{
    Room *room = new Room();
    RoomEffect *effect = new VortexRoom();

    room->setEffect(effect);
    return room;
}

Room *RoomFactory::getPivotRoom(void)
{
    Room *room = new Room();
    RoomEffect *effect = new PivotRoom();

    room->setEffect(effect);
    return room;
}

/* }}} */
/* {{{ Safe room */

Room *RoomFactory::getGearRoom(void)
{
    Room *room = new Room();
    RoomEffect *effect = new GearRoom();

    room->setEffect(effect);
    return room;
}

Room *RoomFactory::getVisionRoom(void)
{
    Room *room = new Room();
    RoomEffect *effect = new VisionRoom();

    room->setEffect(effect);
    return room;
}

Room *RoomFactory::getWarpRoom(void)
{
    Room *room = new Room();
    RoomEffect *effect = new WarpRoom();

    room->setEffect(effect);
    return room;
}

Room *RoomFactory::getCenterRoom(void)
{
    Room *room = new Room();
    RoomEffect *effect = new RoomEffect(ROOM_KIND_CENTER);

    room->setEffect(effect);
    return room;
}

Room *RoomFactory::getExitRoom(void)
{
    Room *room = new Room();
    RoomEffect *effect = new RoomEffect(ROOM_KIND_EXIT);

    room->setEffect(effect);
    return room;
}

Room *RoomFactory::getSafeRoom(void)
{
    Room *room = new Room();
    RoomEffect *effect = new RoomEffect(ROOM_KIND_SAFE);

    room->setEffect(effect);
    return room;
}

/* }}} */
