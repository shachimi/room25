#include "player/away-player.hh"
#include "network/message.hh"

AwayPlayer::AwayPlayer(int id)
    : Player(id)
{
}

AwayPlayer::~AwayPlayer(void)
{
}

Scheduling *AwayPlayer::getScheduling(void)
{
}

bool AwayPlayer::useAction(void)
{
}

direction_t AwayPlayer::selectMove(int allowed_dir)
{
}

direction_t AwayPlayer::selectSlide(int allowed_dir)
{
}


direction_t AwayPlayer::selectSee(int allowed_dir)
{
}

direction_t AwayPlayer::selectPushDirection(int allowed_dir)
{
}

Avatar *AwayPlayer::selectPushTarget(std::vector<Avatar *> players)
{
}

Cell* AwayPlayer::selectCell(std::vector<Cell *> allowed_cells)
{
}

void AwayPlayer::seeRoom(const Room *room)
{
}

