#include "freeze-room.hh"

FreezeRoom::FreezeRoom(void)
{
}

FreezeRoom::~FreezeRoom(void)
{
}

bool FreezeRoom::validateSchedule(Scheduling *scheduling)
{
    return scheduling->getAction1() == ACTION_NONE
        || scheduling->getAction2() == ACTION_NONE;
}
