#include "warp-room.hh"

WarpRoom::WarpRoom(void)
    : RoomEffect(ROOM_KIND_SAFE)
{
}

WarpRoom::~WarpRoom(void)
{
}

void WarpRoom::prisoner_enter(Avatar *avatar)
{
    int pos, dir, allowed_dir = 0;
    Prisoner *prisoner;
    std::vector<Cell *> cells;
    std::vector<Cell *>::iterator it_cells;
    Cell *choosen_cell;
    Room *tmp_room;
    Cell *tmp_cell;


    //Get all possible rooms
    cells = Game::getInstance()->getBoard()->getNoCenterCells();

    for (it_cells = cells.begin(); it_cells < cells.end(); it_cells++) {
        if ((*it_cells)->getRoom()->isVisible())
            cells.erase(it_cells);
        else
            (*it_cells)->getRoom()->setPrintParamAllowed(true);
    }
    Log::print() << *Game::getInstance()->getBoard();
    for (it_cells = cells.begin(); it_cells < cells.end(); it_cells++) {
        (*it_cells)->getRoom()->setPrintParamAllowed(false);
    }

    //Choose one possible
    choosen_cell = prisoner->getOwner()->selectCell(cells);
    if (choosen_cell == NULL) {
        Log::error("Gear room enter") << "Failed to select room" << std::endl;
        return;
    }
    
    //Exchange rooms
    tmp_room = choosen_cell->getRoom();
    tmp_cell = avatar->getRoom()->getCell();
    choosen_cell->setRoom(avatar->getRoom());
    tmp_cell->setRoom(tmp_room);
}

void WarpRoom::turn_starts(void)
{
}

void WarpRoom::prisoner_stay(Avatar *prisoner)
{
}

void WarpRoom::turn_ends(void)
{
}
