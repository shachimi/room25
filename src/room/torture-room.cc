#include "torture-room.hh"

TortureRoom::TortureRoom(void)
{
}

TortureRoom::~TortureRoom(void)
{
}

void TortureRoom::prisoner_enter(Player *prisoner)
{
}

void TortureRoom::turn_starts(void)
{
}

void TortureRoom::prisoner_stay(Player *prisoner)
{
    prisoner->setIsAlive(false);
}

void TortureRoom::turn_ends(void)
{
}

