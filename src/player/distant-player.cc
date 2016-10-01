#include "player/distant-player.hh"
#include "network/message.hh"
#include "network/network.hh"

direction_t get_direction(int from, int to)
{
    int l = Game::getInstance()->getBoard()->getL();

    //N-S
    if (from/l < to/l) {
        return DIRECTION_N;
    } else if (from/l > to/l) {
        return DIRECTION_S;
    } else {
        //O-E
        if (from%l < to%l) {
            return DIRECTION_O;
        } else if (from%l > to%l) {
            return DIRECTION_E;
        }
    }
}

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

    //return static_cast<Scheduling *>(msg);
    return NULL;
}

bool DistantPlayer::useAction(void)
{
    Message *msg = Network::getInstance()->wait(REQ_USE_ACTION, this->sock);

    return static_cast<UseAction *>(msg)->getValue();
}

direction_t DistantPlayer::selectMove(int allowed_dir)
{
    Move *move = static_cast<Move *>(
        Network::getInstance()->wait(REQ_MOVE, this->sock));

    return get_direction(move->getFrom(), move->getTo());
}

direction_t DistantPlayer::selectSlide(int allowed_dir)
{
    Slide *slide = static_cast<Slide *>(
        Network::getInstance()->wait(REQ_SLIDE, this->sock));

    return slide->dir;
}


direction_t DistantPlayer::selectSee(int allowed_dir)
{
    See *see = static_cast<See *>(
        Network::getInstance()->wait(REQ_SEE, this->sock));

    return get_direction(see->getFrom(), see->getTo());
}

direction_t DistantPlayer::selectPushDirection(int allowed_dir)
{
    Push *push = static_cast<Push *>(
        Network::getInstance()->wait(REQ_PUSH, this->sock));

    return get_direction(push->getFrom(), push->getTo());
}

Avatar *DistantPlayer::selectPushTarget(std::vector<Avatar *> players)
{
    Push *push = static_cast<Push *>(
        Network::getInstance()->wait(REQ_PUSH, this->sock));

    for (int i = 0; i < players; i++) {
        if (players[i] == push->victim_id) {
            return players[i];
        }
    }

    return NULL;
}

Cell* DistantPlayer::selectCell(std::vector<Cell *> allowed_cells)
{
    SelectCell *selectCell = static_cast<SelectCell *>(
        Network::getInstance()->wait(REQ_SELECT_CELL, this->sock));

    return Game::getInstance()->getBoard()->getCell(selectCell->pos);
}

room_kind_t DistantPlayer::seeRoom(const Room *room)
{
    // Send message to all clients ?
}
