#include "deadly-room.hh"

DeadlyRoom::DeadlyRoom(void)
    : RoomEffect(ROOM_KIND_DANGER)
{
}

DeadlyRoom::~DeadlyRoom(void)
{
}

void DeadlyRoom::prisoner_enter(Avatar *avatar, Cell *from)
{
    avatar->destroy();
}
