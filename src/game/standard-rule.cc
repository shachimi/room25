#include "board/room-factory.hh"
#include "game/standard-rule.hh"


StandardRule::StandardRule(void)
{
}

StandardRule::~StandardRule(void)
{
}

Board *StandardRule::init_board(std::vector<RoomEffect *> rooms)
{
    std::vector<Room *> rooms;

    /* 4 deadly room */
    rooms.push_back(RoomFactory::getDeadlyRoom());
    rooms.push_back(RoomFactory::getDeadlyRoom());
    rooms.push_back(RoomFactory::getDeadlyRoom());
    rooms.push_back(RoomFactory::getDeadlyRoom());

    /* 10 safe room */
    room.push_back(RoomFactory::getSafeRoom());
    room.push_back(RoomFactory::getSafeRoom());
    room.push_back(RoomFactory::getSafeRoom());
    room.push_back(RoomFactory::getSafeRoom());
    room.push_back(RoomFactory::getSafeRoom());
    room.push_back(RoomFactory::getSafeRoom());
    room.push_back(RoomFactory::getSafeRoom());
    room.push_back(RoomFactory::getSafeRoom());
    room.push_back(RoomFactory::getSafeRoom());
    room.push_back(RoomFactory::getSafeRoom());

    /* 5 flooding room */
    rooms.push_back(RoomFactory::getFloodingRoom());
    rooms.push_back(RoomFactory::getFloodingRoom());
    rooms.push_back(RoomFactory::getFloodingRoom());
    rooms.push_back(RoomFactory::getFloodingRoom());
    rooms.push_back(RoomFactory::getFloodingRoom());

    /* 3 acid room */
    rooms.push_back(RoomFactory::getAcidRoom());
    rooms.push_back(RoomFactory::getAcidRoom());
    rooms.push_back(RoomFactory::getAcidRoom());

    /* 2 torture room */
    rooms.push_back(RoomFactory::getTortureRoom());
    rooms.push_back(RoomFactory::getTortureRoom());

    return new Board(rooms);
}

bool StandardRule::destroyPrisoner(Prisoner *prisoner)
{
    return true;
}

