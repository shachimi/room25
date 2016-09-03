#include "player/prisoner.hh"
#include "room.hh"

static std::string printBgRed = "\033[41m";
static std::string printBgGreen = "\033[42;30m";
static std::string printBgDefault = "\033[0m";

Room::Room(void)
    : avatars(std::vector<Avatar *>()),
      cell(NULL),
      effect(NULL),
      visible(false),
      accessible(true),
      printParamAllowed(false)
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

bool Room::validateSchedule(Scheduling *scheduling)
{
    return this->effect->validateSchedule(scheduling);
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

    if (this->printParamAllowed) {
        out << printBgGreen;
    }

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
        if (this->printParamAllowed) {
            out << printBgDefault;
        }
        return;
    }
    out << (is_avatar_here[cpt] ? "P" : " ")
        << (is_avatar_here[cpt + 1] ? "P" : " ")
        << (is_avatar_here[cpt + 2] ? "P" : " ");

    if (this->printParamAllowed) {
        out << printBgDefault;
    }
}

room_kind_t Room::getRoomKind(void) const
{
    return this->effect->getKind();
}

void Room::setEffect(RoomEffect *effect)
{
    if (this->effect) {
        this->effect->setRoom(NULL);
    }
    this->effect = effect;
    this->effect->setRoom(this);
}

