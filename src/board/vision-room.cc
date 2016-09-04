# include "vision-room.hh"
# include "utils/utils.hh"

VisionRoom::VisionRoom(void)
    : RoomEffect(ROOM_KIND_SAFE)
{
}

VisionRoom::~VisionRoom(void)
{
}

void VisionRoom::prisoner_enter(Avatar *avatar)
{
    int pos, dir, allowed_dir = 0;
    Prisoner *prisoner;
    std::vector<Cell *> cells;
    std::vector<Cell *>::iterator it_cells;
    Cell *choosen_cell;

    //Init
    if ( (prisoner = static_cast<Prisoner *>(avatar)) == NULL) {
        Log::error("Vision room enter") << "Not a prisonner" << std::endl;
        return;
    }
    //Get all possible rooms
    cells = Game::getInstance()->getBoard()->getNoCenterCells();

    for (it_cells = cells.begin(); it_cells < cells.end(); it_cells++) {
        (*it_cells)->getRoom()->setPrintParamAllowed(true);
    }
    Log::print() << *Game::getInstance()->getBoard();
    for (it_cells = cells.begin(); it_cells < cells.end(); it_cells++) {
        (*it_cells)->getRoom()->setPrintParamAllowed(false);
    }

    //Choose one possible
    choosen_cell = prisoner->getOwner()->selectCell(cells);
    if (choosen_cell == NULL) {
        Log::error("Vision room enter") << "Failed to select room" << std::endl;
        return;
    }

    prisoner->getOwner()->seeRoom(choosen_cell->getRoom());

}

void VisionRoom::turn_starts(void)
{
}

void VisionRoom::prisoner_stay(Avatar *prisoner)
{
}

void VisionRoom::turn_ends(void)
{
}

