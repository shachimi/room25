#include "acid-room.hh"

AcidRoom::AcidRoom(void)
    : RoomEffect(ROOM_KIND_DANGER)
{
}

AcidRoom::~AcidRoom(void)
{
}

void AcidRoom::prisoner_enter(Avatar *prisoner)
{
    std::vector<Avatar *> avatars = this->room->getAvatars();

    for (int i = 0; i < avatars.size(); i++) {
        if (avatars[i] != prisoner) {
            avatars[i]->destroy();
        }
    }
}

