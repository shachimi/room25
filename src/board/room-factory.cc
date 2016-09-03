#include "board/flooding-room.hh"
#include "board/deadly-room.hh"
#include "board/acid-room.hh"
#include "board/torture-room.hh"
#include "board/room-factory.hh"
#include "board/gear-room.hh"


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

Room *RoomFactory::getGearRoom(void)
{
    Room *room = new Room();
    RoomEffect *effect = new GearRoom();

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
