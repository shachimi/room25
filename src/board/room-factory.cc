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
#include "board/tunnel-room.hh"

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

Room *RoomFactory::getTunnelRoom(void)
{
    Room *room = new Room();
    RoomEffect *effect = new TunnelRoom();

    room->setEffect(effect);
    return room;
}

/* }}} */

Room *RoomFactory::getRoom(effect_t effect)
{
    switch(effect)
    {
      case EFFECT_DEADLY:
        return RoomFactory::getDeadlyRoom();
        break;
      case EFFECT_ACID:
        return RoomFactory::getAcidRoom();
        break;
      case EFFECT_FLOODING:
        return RoomFactory::getFloodingRoom();
        break;
      case EFFECT_TORTURE:
        return RoomFactory::getTortureRoom();
        break;
      case EFFECT_ILLUSION:
        return RoomFactory::getIllusionRoom();
        break;

      case EFFECT_FREEZE:
        return RoomFactory::getFreezeRoom();
        break;
      case EFFECT_PRISON:
        return RoomFactory::getPrisonRoom();
        break;
      case EFFECT_FOG:
        return RoomFactory::getFogRoom();
        break;
      case EFFECT_VORTEX:
        return RoomFactory::getVortexRoom();
        break;
      case EFFECT_PIVOT:
        return RoomFactory::getPivotRoom();
        break;

      case EFFECT_CENTER:
        return RoomFactory::getCenterRoom();
        break;
      case EFFECT_EXIT:
        return RoomFactory::getExitRoom();
        break;
      case EFFECT_SAFE:
        return RoomFactory::getSafeRoom();
        break;
      case EFFECT_GEAR:
        return RoomFactory::getGearRoom();
        break;
      case EFFECT_VISION:
        return RoomFactory::getVisionRoom();
        break;
      case EFFECT_WARP:
        return RoomFactory::getWarpRoom();
        break;
      case EFFECT_TUNNEL:
        return RoomFactory::getTunnelRoom();
        break;
    }
}
