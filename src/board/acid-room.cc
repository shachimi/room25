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
    std::vector<Avatar *> players = this->room->getAvatars();

    for (int i = 0; i < players.size(); i++) {
        if (players[i] != prisoner) {
            // players[i]->setIsAlive(false);
        }
    }
}

void AcidRoom::turn_starts(void)
{
}

void AcidRoom::prisoner_stay(Avatar *prisoner)
{
}

void AcidRoom::turn_ends(void)
{
}

