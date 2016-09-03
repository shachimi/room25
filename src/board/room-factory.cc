#include "flooding-room.hh"
#include "deadly-room.hh"
#include "acid-room.hh"
#include "torture-room.hh"
#include "freeze-room.hh"
#include "prison-room.hh"
#include "fog-room.hh"
#include "room-factory.hh"

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

/* }}} */
/* {{{ Safe room */

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
