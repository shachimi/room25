#include "player/distant-player.hh"
#include "network/message.hh"
#include "network/network.hh"

DistantPlayer::DistantPlayer(int id)
    : Player(id),
      sock(0)
{
    this->sock = Network::getInstance()->server_accept();
}

DistantPlayer::~DistantPlayer(void)
{
}

Scheduling *DistantPlayer::getScheduling(void)
{
    Message *msg = Network::getInstance()->wait(REQ_SCHED, this->sock);

    Log::print() << msg->to_str();
}

bool DistantPlayer::useAction(void)
{
    Message *msg = Network::getInstance()->wait(REQ_USE_ACTION, this->sock);

    Log::print() << msg->to_str();
}

direction_t DistantPlayer::selectMove(int allowed_dir)
{
    Message *msg = Network::getInstance()->wait(REQ_MOVE, this->sock);

    Log::print() << msg->to_str();
}

direction_t DistantPlayer::selectSlide(int allowed_dir)
{
    Message *msg = Network::getInstance()->wait(REQ_SLIDE, this->sock);

    Log::print() << msg->to_str();
}


direction_t DistantPlayer::selectSee(int allowed_dir)
{
    Message *msg = Network::getInstance()->wait(REQ_SEE, this->sock);

    Log::print() << msg->to_str();
}

direction_t DistantPlayer::selectPushDirection(int allowed_dir)
{
    Message *msg = Network::getInstance()->wait(REQ_PUSH, this->sock);

    Log::print() << msg->to_str();
}

Avatar *DistantPlayer::selectPushTarget(std::vector<Avatar *> players)
{
    Message *msg = Network::getInstance()->wait(REQ_PUSH, this->sock);

    Log::print() << msg->to_str();
}

Cell* DistantPlayer::selectCell(std::vector<Cell *> allowed_cells)
{
    Message *msg = Network::getInstance()->wait(REQ_SELECT_CELL, this->sock);

    Log::print() << msg->to_str();
}

void DistantPlayer::seeRoom(const Room *room)
{
    Message *msg = Network::getInstance()->wait(REQ_SEE, this->sock);

    Log::print() << msg->to_str();
}
