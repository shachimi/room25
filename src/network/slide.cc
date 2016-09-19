#include <stdio.h>
#include "network/slide.hh"
#include "game/game.hh"

Slide::Slide(void)
{
}

Slide::Slide(int id, int from, direction_t dir)
    : id(id),
      from(from),
      dir(dir)
{
}

Slide::~Slide(void)
{
}

std::string Slide::to_str(void)
{
    char str[255];
    int l = Game::getInstance()->getBoard()->getL();

    snprintf(str, 255, "Player %d has slided to %d from (%d, %d)",
             this->id, this->dir, (this->from % l) + 1, (this->from / l) + 1);
    return std::string(str);
}

net_msg_t Slide::to_net_msg(void)
{
    net_msg_t msg;
    net_slide_t slide;

    slide.id = this->id;
    slide.from = this->from;
    slide.dir = this->dir;

    msg.req = REQ_SLIDE;
    msg.slide = slide;

    return msg;
}
