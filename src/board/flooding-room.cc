#include "flooding-room.hh"

FloodingRoom::FloodingRoom(void)
    : flooded_cpt(0)
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

void FloodingRoom::turn_starts(void)
{
}

void FloodingRoom::prisoner_stay(Avatar *prisoner)
{
}

void FloodingRoom::turn_ends(void)
{
    if (this->flooded_cpt > 0) {
        this->flooded_cpt--;
    } else {
        std::vector<Avatar *> players = this->room->getAvatars();

        for (int i = 0; i < players.size(); i++) {
            // players[i]->setIsAlive(false);
        }
    }
}

