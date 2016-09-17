#include <stdio.h>
#include "network/select-cell.hh"
#include "game/game.hh"

SelectCell::SelectCell(void)
{
}

SelectCell::SelectCell(int id, int pos, effect_t effect)
    :id(id),
     pos(pos),
     effect(effect)
{
}

SelectCell::~SelectCell(void)
{
}

std::string SelectCell::to_str(void)
{
    char str[255];
    int l = Game::getInstance()->getBoard()->getL();

    snprintf(str, 255, "Player %d has choosen cell (%d, %d) due to %s",
             this->id, (this->pos % l) + 1, (this->pos % l) + 1,
             effect_to_str(this->effect).c_str());
    return std::string(str);
}

// net_msg_t SelectCell::to_net_msg(void)
// {
// }

