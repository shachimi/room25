#include "player.hh"

Player::Player(int id)
    : id(id),
      actions_stock(ACTION_ALL),
      avatar(NULL)
{
}

Player::~Player(void)
{
}

