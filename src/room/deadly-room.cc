#include "deadly-room.hh"

DeadlyRoom::DeadlyRoom(void)
    : RoomEffect(ROOM_KIND_DANGER)
{
}

DeadlyRoom::~DeadlyRoom(void)
{
}

void DeadlyRoom::prisoner_enter(Player *prisoner)
{
    // Game *game = Game::getInstance();

    prisoner->setIsAlive(false);
}

void DeadlyRoom::turn_starts(void)
{
}

void DeadlyRoom::prisoner_stay(Player * prisoner)
{
}

void DeadlyRoom::turn_ends(void)
{
}

