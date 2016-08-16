#include "room.hh"

Room::Room(void)
    : players(std::vector<Player *>()),
      cell(NULL),
      effect(NULL),
      visible(false)
{
}

Room::~Room(void)
{
}

void Room::addPlayer(Player *player, bool activate_effect)
{
    this->players.push_back(player);
    player->setRoom(this);

    if (activate_effect) {
        this->visible = true;
        this->effect->prisoner_enter(player);
    }
}

void Room::removePlayer(Player *player)
{
    std::vector<Player *>::iterator it;

    for (it = this->players.begin() ; it != this->players.end(); ++it) {
        if (*it == player) {
            this->players.erase(it);
            return;
        }
    }
}

void Room::print(std::ostream& out)
{
    if (this->visible) {
        this->effect->print(out);
    } else
    if (this->players.size() > 0) {
        out << "P";
    } else {
        out << " ";
    }
    out << "|";
}


void Room::setEffect(RoomEffect *effect)
{
    if (this->effect) {
        this->effect->setRoom(NULL);
    }
    this->effect = effect;
    this->effect->setRoom(this);
}
