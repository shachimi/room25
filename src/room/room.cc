#include "player/prisoner.hh"
#include "room.hh"

Room::Room(void)
    : avatars(std::vector<Avatar *>()),
      cell(NULL),
      effect(NULL),
      visible(false)
{
}

Room::~Room(void)
{
}

void Room::addAvatar(Avatar *avatar, bool activate_effect)
{
    this->avatars.push_back(avatar);
    avatar->setRoom(this);

    if (activate_effect) {
        this->visible = true;
        this->effect->prisoner_enter(avatar);
    }
}

void Room::removeAvatar(Avatar *avatar)
{
    std::vector<Avatar *>::iterator it;

    for (it = this->avatars.begin() ; it != this->avatars.end(); ++it) {
        if (*it == avatar) {
            this->avatars.erase(it);
            return;
        }
    }
}

void Room::print(std::ostream& out)
{
    if (this->visible) {
        this->effect->print(out);
    } else
    if (this->avatars.size() > 0) {
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
