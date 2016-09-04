#include "illusion-room.hh"

IllusionRoom::IllusionRoom(void)
    : RoomEffect(ROOM_KIND_DANGER)
{
}

IllusionRoom::~IllusionRoom(void)
{
}

void IllusionRoom::prisoner_enter(Avatar *avatar, Cell *from)
{
    int pos, dir, allowed_dir = 0;
    Prisoner *prisoner;
    std::vector<Cell *> cells;
    std::vector<Cell *>::iterator it_cells;
    Cell *choosen_cell;
    RoomEffect *tmp_room_effect;

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
    tmp_room_effect = choosen_cell->getRoom()->getEffect();
    choosen_cell->getRoom()->setEffect(avatar->getRoom()->getEffect());
    avatar->getRoom()->setEffect(tmp_room_effect);

    tmp_room_effect->prisoner_enter(avatar, from);
}
