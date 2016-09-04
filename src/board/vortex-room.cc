#include "vortex-room.hh"
#include "game/game.hh"

VortexRoom::VortexRoom(void)
    : RoomEffect(ROOM_KIND_DANGER)
{
}

VortexRoom::~VortexRoom(void)
{
}

void VortexRoom::prisoner_enter(Avatar *avatar, Cell *from)
{
    Game::getInstance()->getBoard()->set_avatar_to_center(avatar);
}
