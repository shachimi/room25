#include "torture-room.hh"

TortureRoom::TortureRoom(void)
    : RoomEffect(ROOM_KIND_DANGER)
{
}

TortureRoom::~TortureRoom(void)
{
}

void TortureRoom::prisoner_stay(Avatar *prisoner)
{
    prisoner->destroy();
}

