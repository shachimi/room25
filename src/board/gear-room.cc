# include "gear-room.hh"
# include "utils/utils.hh"

GearRoom::GearRoom(void)
    : RoomEffect(ROOM_KIND_SAFE)
{
}

GearRoom::~GearRoom(void)
{
}

void GearRoom::prisoner_enter(Avatar *avatar, Cell *from)
{
    int pos, dir, allowed_dir = 0;
    Prisoner *prisoner;
    std::vector<Cell *> cells;
    std::vector<Cell *>::iterator it_cells;
    Cell *choosen_cell;

    //Init
    if ( (prisoner = static_cast<Prisoner *>(avatar)) == NULL) {
        Log::error("Gear room enter") << "Not a prisonner" << std::endl;
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
        Log::error("Gear room enter") << "Failed to select room" << std::endl;
        return;
    }

    pos = choosen_cell->getPos();
    //Choose direction from choosen room
    if (pos % 5 /* x */ != 2) {
        allowed_dir |= DIRECTION_N | DIRECTION_S;
    }
    if (pos / 5 /* y */ != 2) {
        allowed_dir |= DIRECTION_O | DIRECTION_E;
    }

    if (!allowed_dir) {
        std::cerr << "you cannot slide in this cell" << std::endl;
        return;
    }
    dir = prisoner->getOwner()->selectSlide(allowed_dir);

    if (!(dir & allowed_dir)) {
        Log::error("Gear room enter") << "Failed to select direction" << std::endl;
        return;
    }
    Game::getInstance()->getBoard()->slide(
            choosen_cell->getX(),
            choosen_cell->getY(), (direction_t)dir);
}

