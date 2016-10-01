#include <stdio.h>
#include "network/get-scheduling.hh"
#include "game/game.hh"

GetScheduling::GetScheduling(void)
{
}

GetScheduling::GetScheduling(int id, int adrenaline,
                             action_t action_1, action_t action_2)
    :id(id),
     adrenaline(adrenaline),
     action_1(action_1),
     action_2(action_2)
{
}

GetScheduling::~GetScheduling(void)
{
}

std::string GetScheduling::to_str(void)
{
    char str[255];
    int l = Game::getInstance()->getBoard()->getL();

    snprintf(str, 255, "Player %d has scheduled action (%d, %d) and has %sused its adrenaline",
             this->id, this->action_1, this->action_2,
             this->adrenaline ? "" : "not ");
    return str;
}

net_msg_t GetScheduling::to_net_msg(void)
{
    net_msg_t msg;
    net_scheduling_t scheduling;

    scheduling.player_id = this->id;
    scheduling.adrenaline = this->adrenaline;
    scheduling.action_1 = this->action_1;
    scheduling.action_2 = this->action_2;

    msg.req = REQ_SCHED;
    msg.scheduling = scheduling;

    return msg;
}




