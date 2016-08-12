#include "human_player.hh"
#include <assert.h>


Action *HumanPlayer::getAction(void)
{
    return NULL;
}

direction_t HumanPlayer::execMove(int allowed_dir)
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
