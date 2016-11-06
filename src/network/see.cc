#include <stdio.h>
#include "network/see.hh"
#include "game/game.hh"

See::See(void)
{
}

See::See(int id, int from, int to)
    :Message(id),
     from(from),
     to(to)
{
}

See::~See(void)
{
}

std::string See::to_str(void)
{
    char str[255];
    int l = Game::getInstance()->getBoard()->getL();

    snprintf(str, 255, "Player %d has seen (%d, %d) from (%d, %d)",
             this->id, (this->to % l) + 1, (this->to / l) + 1,
             (this->from % l) + 1, (this->from / l) + 1);
    return std::string(str);
}

net_msg_t See::to_net_msg(void)
{
    net_msg_t msg;
    net_see_t see;

    see.id = this->id;
    see.from = this->from;
    see.to = this->to;

    msg.req = REQ_SEE;
    msg.see = see;

    return msg;
}
