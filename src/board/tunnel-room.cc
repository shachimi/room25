# include "tunnel-room.hh"
# include "utils/utils.hh"
# include "player/prisoner.hh"
# include "utils/Log.hh"
# include "game/game.hh"

TunnelRoom::TunnelRoom(void)
    : RoomEffect(ROOM_KIND_SAFE)
{
}

TunnelRoom::~TunnelRoom(void)
{
}

void TunnelRoom::prisoner_enter(Avatar *avatar)
{
    int pos, dir, allowed_dir = 0;
    Prisoner *prisoner;
    std::vector<RoomEffect *> tunnel_room_effects;
    std::vector<RoomEffect *>::iterator it;
    std::vector<Cell *> cells;
    Cell *choosen_cell;

    //Init
    if ( (prisoner = static_cast<Prisoner *>(avatar)) == NULL) {
        Log::error("Tunnel room enter") << "Not a prisonner" << std::endl;
        return;
    }
    //Get all possible rooms
    tunnel_room_effects = Game::getInstance()->getBoard()->getTunnelRoomEffects();

    for (it = tunnel_room_effects.begin(); it < tunnel_room_effects.end(); it++) {
        if ((*it) != this && (*it)->getRoom()->isVisible()) {
            (*it)->getRoom()->setPrintParamAllowed(true);
            cells.push_back((*it)->getRoom()->getCell());
        }
    }
    Log::print() << *Game::getInstance()->getBoard();
    for (it = tunnel_room_effects.begin(); it < tunnel_room_effects.end(); it++) {
        (*it)->getRoom()->setPrintParamAllowed(false);
    }

    //Choose one possible
    choosen_cell = prisoner->getOwner()->selectCell(cells);
    if (choosen_cell == NULL) {
        Log::error("Tunnel room enter") << "Failed to select room" << std::endl;
        return;
    }
    
    prisoner->setRoom(choosen_cell->getRoom());
}


