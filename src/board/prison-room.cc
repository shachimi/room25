#include "prison-room.hh"

PrisonRoom::PrisonRoom(void)
    : RoomEffect(ROOM_KIND_OBS)
{
}

PrisonRoom::~PrisonRoom(void)
{
}


int PrisonRoom::validateDirection(int directions, action_t action)
{
    if (action == ACTION_MOVE) {
        int allowed_dir = DIRECTION_NONE;
        Cell *cell = this->room->getCell();

        if (directions & DIRECTION_N && cell->getUp()
        && (cell->getUp()->getRoom()->getAvatarsNb()
        ||  cell->getUp()->getRoomKind() == ROOM_KIND_CENTER))
        {
            allowed_dir |= DIRECTION_N;
        } else
        if (directions & DIRECTION_O && cell->getLeft()
        && (cell->getLeft()->getRoom()->getAvatarsNb()
        ||  cell->getUp()->getRoomKind() == ROOM_KIND_CENTER))
        {
            allowed_dir |= DIRECTION_O;
        } else
        if (directions & DIRECTION_S && cell->getDown()
        && (cell->getDown()->getRoom()->getAvatarsNb()
        ||  cell->getUp()->getRoomKind() == ROOM_KIND_CENTER))
        {
            allowed_dir |= DIRECTION_S;
        } else
        if (directions & DIRECTION_E && cell->getRight()
        && (cell->getRight()->getRoom()->getAvatarsNb()
        ||  cell->getUp()->getRoomKind() == ROOM_KIND_CENTER))
        {
            allowed_dir |= DIRECTION_E;
        }
        return allowed_dir;
    }

    return directions;
}
