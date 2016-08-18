#include "scheduling.hh"

Scheduling::Scheduling(void)
    : adrenaline(false),
      action_1(ACTION_NONE),
      action_2(ACTION_NONE),
      owner(NULL)
{
}

Scheduling::~Scheduling(void)
{
}

action_t Scheduling::getAction(int turn) const
{
    return turn == 1 ? this->action_1 : this->action_2;
}
