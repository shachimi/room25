#include "acid-room.hh"

AcidRoom::AcidRoom(void)
{
}

AcidRoom::~AcidRoom(void)
{
}

void AcidRoom::prisoner_enter(Player *prisoner)
{
    std::vector<Player *> players = this->room->getPlayers();

    for (int i = 0; i < players.size(); i++) {
        if (players[i] != prisoner) {
            players[i]->setIsAlive(false);
        }
    }
}

void AcidRoom::turn_starts(void)
{
}

void AcidRoom::prisoner_stay(Player * prisoner)
{
}

void AcidRoom::turn_ends(void)
{
}

