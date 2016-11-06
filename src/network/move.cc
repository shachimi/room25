#include <stdio.h>
#include "network/move.hh"
#include "game/game.hh"

Move::Move(void)
{
}

Move::Move(int id, int from, int to, effect_t to_effect)
    :Message(id),
     from(from),
     to(to),
     to_effect(to_effect)
{
}

Move::~Move(void)
{
}

std::string Move::to_str(void)
{
    char str[255];
    int l = Game::getInstance()->getBoard()->getL();

    snprintf(str, 255, "Plyaer %d has moved from (%d, %d) to (%d, %d)",
             this->id, (this->from % l) + 1, (this->from / l) + 1,
             (this->to % l) + 1, (this->to / l) + 1);
    return str;
}

net_msg_t Move::to_net_msg(void)
{
    net_msg_t msg;
    net_move_t move;

    move.id = this->id;
    move.from = this->from;
    move.to = this->to;
    move.to_effect = this->to_effect;

    msg.req = REQ_MOVE;
    msg.move = move;

    return msg;
}
