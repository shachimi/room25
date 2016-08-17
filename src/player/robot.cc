#include "robot.hh"
#include "game/game.hh"

Robot::Robot(void)
    : Avatar()
{
}

Robot::~Robot(void)
{
}

void Robot::destroy(void)
{
    Game::getInstance()->removeAvatar(this);
}
