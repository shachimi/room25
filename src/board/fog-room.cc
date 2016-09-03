#include "fog-room.hh"

FogRoom::FogRoom(void)
    : RoomEffect(ROOM_KIND_OBS)
{
}

FogRoom::~FogRoom(void)
{
}


int FogRoom::validateDirection(int directions, action_t action)
{
    return action != ACTION_SEE ? directions : DIRECTION_NONE;
}

