#include <stdio.h>
#include "network/push.hh"
#include "game/game.hh"

Push::Push(void)
{
}

Push::Push(int id, int victim_id, int from, int to)
    :id(id),
     victim_id(victim_id),
     from(from),
     to(to)
{
}

Push::~Push(void)
{
}

std::string Push::to_str(void)
{
    char str[255];
    int l = Game::getInstance()->getBoard()->getL();

    snprintf(str, 255, "Player %d has pushed player %d from (%d, %d) to (%d, %d)",
             this->id, this->victim_id, (this->from % l) + 1,
             (this->from / l) + 1, (this->to % l) + 1, (this->to / l) + 1);
    return str;
}

// net_msg_t Push::to_net_msg(void)
// {
// }