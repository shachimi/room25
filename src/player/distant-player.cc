#include "player/distant-player.hh"
#include "network/message.hh"
#include "network/network.hh"

DistantPlayer::DistantPlayer(int id)
    : Player(id)
{
}

DistantPlayer::~DistantPlayer(void)
{
}

Scheduling *DistantPlayer::getScheduling(void)
{
    Message *msg = Network::getInstance()->wait(REQ_SCHED);

    Log::print() << msg->to_str();
}

bool DistantPlayer::useAction(void)
{
    Message *msg = Network::getInstance()->wait(REQ_USE_ACTION);

    Log::print() << msg->to_str();
}

direction_t DistantPlayer::selectMove(int allowed_dir)
{
    Message *msg = Network::getInstance()->wait(REQ_MOVE);

    Log::print() << msg->to_str();
}

direction_t DistantPlayer::selectSlide(int allowed_dir)
{
    Message *msg = Network::getInstance()->wait(REQ_SLIDE);

    Log::print() << msg->to_str();
}


direction_t DistantPlayer::selectSee(int allowed_dir)
{
    Message *msg = Network::getInstance()->wait(REQ_SEE);

    Log::print() << msg->to_str();
}

direction_t DistantPlayer::selectPushDirection(int allowed_dir)
{
    Message *msg = Network::getInstance()->wait(REQ_PUSH);

    Log::print() << msg->to_str();
}

Avatar *DistantPlayer::selectPushTarget(std::vector<Avatar *> players)
{
    Message *msg = Network::getInstance()->wait(REQ_PUSH);

    Log::print() << msg->to_str();
}

Cell* DistantPlayer::selectCell(std::vector<Cell *> allowed_cells)
{
    Message *msg = Network::getInstance()->wait(REQ_SELECT_CELL);

    Log::print() << msg->to_str();
}

void DistantPlayer::seeRoom(const Room *room)
{
    Message *msg = Network::getInstance()->wait(REQ_SEE);

    Log::print() << msg->to_str();
}
