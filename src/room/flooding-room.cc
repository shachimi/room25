#include "flooding-room.hh"

FloodingRoom::FloodingRoom(void)
    : flooded_cpt(0)
{
}

FloodingRoom::~FloodingRoom(void)
{
}

void FloodingRoom::prisoner_enter(Player *prisoner)
{
    this->room->setAccessible(false);
    this->flooded_cpt = 1;
}

void FloodingRoom::turn_starts(void)
{
}

void FloodingRoom::prisoner_stay(Player *prisoner)
{
}

void FloodingRoom::turn_ends(void)
{
    if (this->flooded_cpt > 0) {
        this->flooded_cpt--;
    } else {
        std::vector<Player *> players = this->room->getPlayers();

        for (int i = 0; i < players.size(); i++) {
            players[i]->setIsAlive(false);
        }
    }
}

