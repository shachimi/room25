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

void Room::print(std::ostream& out, int inner_line)
{
    int cpt = (inner_line - 1) * 3;
    bool is_avatar_here[9] = { false };

    for (int i = 0; i < this->avatars.size(); i++) {
        Prisoner *prisoner = static_cast<Prisoner *>(this->avatars[i]);

        if (!prisoner) {
            continue;
        }

        is_avatar_here[prisoner->getOwner()->getId() - 1] = true;
    }

    if (inner_line == 2) {
        out << (is_avatar_here[3] ? "P" : " ");
        if (this->visible) {
            this->effect->print(out);
        } else {
            out << " ";
        }
        out << (is_avatar_here[4] ? "P" : " ");
        return;
    }
    out << (is_avatar_here[cpt] ? "P" : " ")
        << (is_avatar_here[cpt + 1] ? "P" : " ")
        << (is_avatar_here[cpt + 2] ? "P" : " ");
}



void Room::setEffect(RoomEffect *effect)
{
    if (this->effect) {
        this->effect->setRoom(NULL);
    }
    this->effect = effect;
    this->effect->setRoom(this);
}
