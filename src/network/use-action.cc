#include <stdio.h>
#include "network/use-action.hh"

UseAction::UseAction(void)
    :id(0),
     value(false)
{
}

UseAction::UseAction(int id, bool value)
    :id(id),
     value(value)
{
}

UseAction::~UseAction(void)
{
}

std::string UseAction::to_str(void)
{
    char str[255];

    snprintf(str, 255, "Player %d choosed to use his action",
             this->id);
    return std::string(str);
}

net_msg_t UseAction::to_net_msg(void)
{
    net_msg_t msg;
    net_use_action_t ua;

    ua.id = this->id;
    ua.value = this->value;

    msg.req = REQ_USE_ACTION;
    msg.use_action = ua;

    return msg;
}
