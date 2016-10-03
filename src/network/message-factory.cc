#include "message-factory.hh"

Message *MessageFactory::getMessageFromNet(net_msg_t *msg)
{
    switch (msg->req) {
      case REQ_SEE:
        return MessageFactory::getSeeFromNet(msg);
      case REQ_MOVE:
        return MessageFactory::getMoveFromNet(msg);
      case REQ_PUSH:
        return MessageFactory::getPushFromNet(msg);
      case REQ_SLIDE:
        return MessageFactory::getSlideFromNet(msg);
      case REQ_SELECT_CELL:
        return MessageFactory::getSelectCellFromNet(msg);
      case REQ_USE_ACTION:
        return MessageFactory::getUseActionFromNet(msg);
      case REQ_SCHED:
        return MessageFactory::getGetSchedulingFromNet(msg);
    }
    return NULL;
}

See *MessageFactory::getSeeFromNet(net_msg_t *msg)
{
    net_see_t see = msg->see;

    return new See(see.id, see.from, see.to);
}

Move *MessageFactory::getMoveFromNet(net_msg_t *msg)
{
    net_move_t move = msg->move;

    return new Move(move.id, move.from, move.to, move.to_effect);
}

Push *MessageFactory::getPushFromNet(net_msg_t *msg)
{
    net_push_t push = msg->push;

    return new Push(push.id, push.victim_id,
                    push.from, push.to, push.to_effect);
}

Slide *MessageFactory::getSlideFromNet(net_msg_t *msg)
{
    net_slide_t slide = msg->slide;

    return new Slide(slide.id, slide.from, slide.dir);
}

SelectCell *MessageFactory::getSelectCellFromNet(net_msg_t *msg)
{
    net_select_cell_t select_cell = msg->select_cell;

    return new SelectCell(select_cell.id, select_cell.pos,
                          select_cell.effect);
}

UseAction *MessageFactory::getUseActionFromNet(net_msg_t *msg)
{
    net_use_action_t use_action = msg->use_action;

    return new UseAction(use_action.id, use_action.value);
}

GetScheduling *MessageFactory::getGetSchedulingFromNet(net_msg_t *msg)
{
    net_scheduling_t scheduling = msg->scheduling;

    return new GetScheduling(scheduling.player_id, scheduling.adrenaline,
                             scheduling.action_1, scheduling.action_2);
}

PlayerMsg *getPlayerMsgFromNet(net_msg_t *msg)
{
    net_player_t player = msg->player;

    return new UseAction(player.id, player.pos, player.avatar_kind);
}
