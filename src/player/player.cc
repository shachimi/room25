#include <assert.h>

#include "player.hh"
#include "player/prisoner.hh"

Player::Player(int id)
    : id(id),
      actions_stock(ACTION_ALL),
      avatar(NULL)
{
    assert(id > 0);
}

Player::~Player(void)
{
}

bool Player::isAvatarAlive(void)
{
    Prisoner *prisoner = static_cast<Prisoner *>(this->avatar);

    return prisoner && prisoner->isAlive();
}
