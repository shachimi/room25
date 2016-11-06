#include "player/away-player.hh"
#include "network/message.hh"
#include "network/network.hh"
#include "game/game.hh"

direction_t get_direction(int from, int to)
{
    int l = Game::getInstance()->getBoard()->getL();

    //N-S
    if (from / l < to / l) {
        return DIRECTION_N;
    } else
    if (from / l > to / l) {
        return DIRECTION_S;
    } else {
        //O-E
        if (from % l < to % l) {
            return DIRECTION_O;
        } else
        if (from % l > to % l) {
            return DIRECTION_E;
        }
    }
}

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

    return static_cast<UseAction *>(msg)->getValue();
}

direction_t AwayPlayer::selectMove(int allowed_dir)
{
    Move *move = static_cast<Move *>(Network::getInstance()->wait(REQ_MOVE));

    return get_direction(move->getFrom(), move->getTo());
}

direction_t AwayPlayer::selectSlide(int allowed_dir)
{
    Slide *slide = static_cast<Slide *>(
        Network::getInstance()->wait(REQ_SLIDE));

    return slide->getDir();
}


direction_t AwayPlayer::selectSee(int allowed_dir)
{
    See *see = static_cast<See *>(
        Network::getInstance()->wait(REQ_SEE));

    return get_direction(see->getFrom(), see->getTo());
}

direction_t AwayPlayer::selectPushDirection(int allowed_dir)
{
    Push *push = static_cast<Push *>(
        Network::getInstance()->wait(REQ_PUSH));

    return get_direction(push->getFrom(), push->getTo());
}

Avatar *AwayPlayer::selectPushTarget(std::vector<Avatar *> players)
{
    Push *push = static_cast<Push *>(
        Network::getInstance()->wait(REQ_PUSH));

    for (int i = 0; i < players.size(); i++) {
        if (static_cast<Prisoner *>(players[i])->getOwner()->getId() == push->getVictimId()) {
            return players[i];
        }
    }

    return NULL;
}

Cell* AwayPlayer::selectCell(std::vector<Cell *> allowed_cells)
{
    SelectCell *selectCell = static_cast<SelectCell *>(
        Network::getInstance()->wait(REQ_SELECT_CELL));

    return Game::getInstance()->getBoard()->getCell(selectCell->getPos());
}

room_kind_t AwayPlayer::seeRoom(const Room *room)
{
    Message *msg = Network::getInstance()->wait(REQ_SEE);

    Log::print() << msg->to_str();
}

