#include "pivot-room.hh"

PivotRoom::PivotRoom(void)
    : RoomEffect(ROOM_KIND_OBS),
      directions(DIRECTION_N | DIRECTION_S)
{
}

PivotRoom::~PivotRoom(void)
{
}

void PivotRoom::prisoner_enter(Avatar *avatar, Cell *from)
{
    Cell *here = this->room->getCell();

    if (here->getUp() == from || here->getDown() == from) {
        this->directions = DIRECTION_N | DIRECTION_S;
    } else {
        this->directions = DIRECTION_O | DIRECTION_E;
    }
}

int PivotRoom::validateDirection(int directions, action_t action)
{
    return action == ACTION_SLIDE ? direction : direction & this->directions;
}
