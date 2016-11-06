#include <stdio.h>
#include "network/room-message.hh"
#include "game/game.hh"

RoomMsg::RoomMsg(void)
    :Message()
{
}

RoomMsg::RoomMsg(int id, int pos, effect_t effect)
    :Message(id),
     pos(pos),
     effect(effect)
{
}

RoomMsg::~RoomMsg(void)
{
}

std::string RoomMsg::to_str(void)
{
    char str[255];
    snprintf(str, 255, "Room: id (%d) pos (%d) effect (%d)",
             this->getId(), this->pos, this->effect);
    return str;
}

net_msg_t RoomMsg::to_net_msg(void)
{
    net_msg_t msg;
    net_room_t room;

    room.pos = this->getPos();
    room.effect = this->getEffect();

    msg.req = REQ_ROOM;
    msg.room = room;

    return msg;
}
