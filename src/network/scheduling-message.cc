#include <stdio.h>
#include "network/scheduling-message.hh"
#include "game/game.hh"

SchedulingMsg::SchedulingMsg(void)
{
}

SchedulingMsg::SchedulingMsg(int owner, action_t action_1, action_t action_2, int adrenaline)
    :Message(owner),
     action_1(action_1),
     action_2(action_2),
     adrenaline(adrenaline)
{
}

SchedulingMsg::~SchedulingMsg(void)
{
}

std::string SchedulingMsg::to_str(void)
{
    char str[255];
    snprintf(str, 255, "Scheduling: owner (%d) action 1 (%d) action 2 (%d) adrenaline ? %s",
             this->getOwner(), this->action_1, this->action_2,
             this->adrenaline ? "Yes" : "No");
    return str;
}

net_msg_t SchedulingMsg::to_net_msg(void)
{
    net_msg_t msg;
    net_scheduling_t scheduling;

    scheduling.owner = this->getOwner();
    scheduling.action_1 = this->action_1;
    scheduling.action_2 = this->action_2;
    scheduling.adrenaline = this->adrenaline;

    msg.req = REQ_SCHED;
    msg.scheduling = scheduling;

    return msg;
}
