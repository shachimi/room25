#include <stdio.h>
#include "network/player-message.hh"
#include "game/game.hh"

PlayerMsg::PlayerMsg(void)
{
}

PlayerMsg::PlayerMsg(int id, int pos, avatar_kind_t avatar_kind)
    :Message(id),
     pos(pos),
     avatar_kind(avatar_kind)
{
}

PlayerMsg::~PlayerMsg(void)
{
}

std::string PlayerMsg::to_str(void)
{
    char str[255];
    int l = Game::getInstance()->getBoard()->getL();
    snprintf(str, 255, "Player creation: id (%d) pos(%d, %d) avatar_kind (%d)",
             this->id, (this->pos % l) + 1, (this->pos / l) + 1,
             this->avatar_kind);
    return str;
}

net_msg_t PlayerMsg::to_net_msg(void)
{
    net_msg_t msg;
    net_player_t player;

    player.id = this->id;
    player.pos = this->pos;
    player.avatar_kind = this->avatar_kind;

    msg.req = REQ_PLAYER;
    msg.player = player;

    return msg;
}
