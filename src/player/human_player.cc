#include "human_player.hh"
#include <assert.h>


Action *HumanPlayer::getAction(void)
{
    return NULL;
}

direction_t HumanPlayer::selectMove(int allowed_dir)
{
    if (allowed_dir & DIRECTION_N) {
        return DIRECTION_N;
    }
    if (allowed_dir & DIRECTION_O) {
        return DIRECTION_O;
    }
    if (allowed_dir & DIRECTION_S) {
        return DIRECTION_S;
    }
    if (allowed_dir & DIRECTION_E) {
        return DIRECTION_E;
    }
    assert (false);
    return DIRECTION_N;
}

direction_t HumanPlayer::selectSlide(int allowed_dir)
{
    if (allowed_dir & DIRECTION_N) {
        return DIRECTION_N;
    }
    if (allowed_dir & DIRECTION_O) {
        return DIRECTION_O;
    }
    if (allowed_dir & DIRECTION_S) {
        return DIRECTION_S;
    }
    if (allowed_dir & DIRECTION_E) {
        return DIRECTION_E;
    }
    assert (false);
    return DIRECTION_N;
}


direction_t HumanPlayer::selectSee(int allowed_dir)
{
    if (allowed_dir & DIRECTION_N) {
        return DIRECTION_N;
    }
    if (allowed_dir & DIRECTION_O) {
        return DIRECTION_O;
    }
    if (allowed_dir & DIRECTION_S) {
        return DIRECTION_S;
    }
    if (allowed_dir & DIRECTION_E) {
        return DIRECTION_E;
    }
    assert (false);
    return DIRECTION_N;
}

direction_t HumanPlayer::selectPushDirection(int allowed_dir)
{
    if (allowed_dir & DIRECTION_N) {
        return DIRECTION_N;
    }
    if (allowed_dir & DIRECTION_O) {
        return DIRECTION_O;
    }
    if (allowed_dir & DIRECTION_S) {
        return DIRECTION_S;
    }
    if (allowed_dir & DIRECTION_E) {
        return DIRECTION_E;
    }
    assert (false);
    return DIRECTION_N;
}

Avatar *HumanPlayer::selectPushTarget(std::vector<Avatar *> players)
{
    return players.front();
}


void HumanPlayer::seeRoom(const Room *room)
{
    std::cout << "I see a room ";
    room->getEffect()->print(std::cout);
    std::cout << std::endl;
}

