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

action_t Scheduling::getAction(int turn) /* should it be const? */
{
    if (this->action_1 == ACTION_NONE || this->action_2 == ACTION_NONE) {
        action_t res = this->action_1 == ACTION_NONE ? this->action_2
                                                     : this->action_1;

        if (turn == 2) {
            return res;
        }
        if (this->getOwner()->useAction()) {
            this->action_1 = ACTION_NONE;
            this->action_2 = ACTION_NONE;
            return res;
        }

        return ACTION_NONE;
    }

    return turn == 1 ? this->action_1 : this->action_2;
}

bool Scheduling::isValid(void)
{
    return this->owner->getAvatar()->getRoom()->validateSchedule(this)
        && !(this->action_1 & this->action_2);
}
