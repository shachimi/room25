#include "gear-room.hh"

GearRoom::GearRoom(void)
{
}

GearRoom::~GearRoom(void)
{
}

void GearRoom::prisoner_enter(Avatar *avatar)
{
    int dir, allowed_dir;
    Prisoner *prisoner;
    std::vector<Cell *> cells;

    //Init
    if ( (prisoner = static_cast<Prisoner *>(avatar)) == NULL) {
        Log::error("Gear room enter") << "Not a prisonner" << std::endl;
        return;
    }
    //Get all possible rooms
    cells = Game::getInstance()->getBoard()->getNoCenterCells();

    //Choose one possible
    dir = prisoner->getOwner()->selectSlide(allowed_dir);

    //Choose direction from choosen room
    //=> Answer from the player
}

void GearRoom::turn_starts(void)
{
}

void GearRoom::prisoner_stay(Avatar *prisoner)
{
}

void GearRoom::turn_ends(void)
{
}

