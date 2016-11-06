#include <stdio.h>
#include "network/select-cell.hh"
#include "game/game.hh"

SelectCell::SelectCell(void)
    :SelectCell(0, 0, (effect_t)0)
{
}

SelectCell::SelectCell(int id, int pos, effect_t effect)
    :Message(id),
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

net_msg_t SelectCell::to_net_msg(void)
{
    net_msg_t msg;
    net_select_cell_t select_cell;

    select_cell.id = this->id;
    select_cell.pos = this->pos;
    select_cell.effect = this->effect;

    msg.req = REQ_SELECT_CELL;
    msg.select_cell = select_cell;

    return msg;

}

