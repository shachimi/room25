#include "player/away-player.hh"
#include "network/message.hh"
#include "network/network.hh"

AwayPlayer::AwayPlayer(int id)
    : Player(id)
{
}

AwayPlayer::~AwayPlayer(void)
{
}

Scheduling *AwayPlayer::getScheduling(void)
{
    Message *msg = Network::getInstance()->wait(REQ_SCHED);

    Log::print() << msg->to_str();
}

bool AwayPlayer::useAction(void)
{
    Message *msg = Network::getInstance()->wait(REQ_USE_ACTION);

    Log::print() << msg->to_str();
}

direction_t AwayPlayer::selectMove(int allowed_dir)
{
    Message *msg = Network::getInstance()->wait(REQ_MOVE);

    Log::print() << msg->to_str();
}

direction_t AwayPlayer::selectSlide(int allowed_dir)
{
    Message *msg = Network::getInstance()->wait(REQ_SLIDE);

    Log::print() << msg->to_str();
}


direction_t AwayPlayer::selectSee(int allowed_dir)
{
    Message *msg = Network::getInstance()->wait(REQ_SEE);

    Log::print() << msg->to_str();
}

direction_t AwayPlayer::selectPushDirection(int allowed_dir)
{
    Message *msg = Network::getInstance()->wait(REQ_PUSH);

    Log::print() << msg->to_str();
}

Avatar *AwayPlayer::selectPushTarget(std::vector<Avatar *> players)
{
    Message *msg = Network::getInstance()->wait(REQ_PUSH);

    Log::print() << msg->to_str();
}

Cell* AwayPlayer::selectCell(std::vector<Cell *> allowed_cells)
{
    Message *msg = Network::getInstance()->wait(REQ_SELECT_CELL);

    Log::print() << msg->to_str();
}

void AwayPlayer::seeRoom(const Room *room)
{
    Message *msg = Network::getInstance()->wait(REQ_SEE);

    Log::print() << msg->to_str();
}

