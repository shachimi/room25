#include <assert.h>

#include "prisoner.hh"
#include "game/game.hh"

Prisoner::Prisoner(Player *player)
    : Avatar(),
      is_alive(true),
      owner(player)
{
    assert (player && "prisoner should be linked to a Player");
}

Prisoner::~Prisoner(void)
{
}

void Prisoner::destroy(void)
{
    this->is_alive = false;
    Game::getInstance()->removeAvatar(this);
}
