#include "torture-room.hh"

TortureRoom::TortureRoom(void)
    : RoomEffect(ROOM_KIND_DANGER)
{
}

TortureRoom::~TortureRoom(void)
{
}

void TortureRoom::prisoner_enter(Avatar *prisoner)
{
}

void TortureRoom::turn_starts(void)
{
}

void TortureRoom::prisoner_stay(Avatar *prisoner)
{
    // prisoner->setIsAlive(false);
}

void TortureRoom::turn_ends(void)
{
}

