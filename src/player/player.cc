#include "player.hh"
#include "player/prisoner.hh"

Player::Player(int id)
    : id(id),
      actions_stock(ACTION_ALL),
      avatar(NULL)
{
}

Player::~Player(void)
{
}

bool Player::isAvatarAlive(void)
{
    Prisoner *prisoner = static_cast<Prisoner *>(this->avatar);

    return prisoner && prisoner->isAlive();
}
