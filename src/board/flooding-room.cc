#include "flooding-room.hh"

FloodingRoom::FloodingRoom(void)
    : RoomEffect(ROOM_KIND_DANGER),
      flooded_cpt(0)
{
}

FloodingRoom::~FloodingRoom(void)
{
}

void FloodingRoom::prisoner_enter(Avatar *prisoner)
{
    this->room->setAccessible(false);
    this->flooded_cpt = 1;
}

void FloodingRoom::turn_ends(void)
{
    if (this->flooded_cpt > 0) {
        this->flooded_cpt--;
    } else {
        std::vector<Avatar *> avatars = this->room->getAvatars();

        for (int i = 0; i < avatars.size(); i++) {
            avatars[i]->destroy();
        }
    }
}

