#include "term-player.hh"
#include <assert.h>
#include <iostream>

TermPlayer::TermPlayer(int id)
    : Player(id)
{
}

TermPlayer::~TermPlayer(void)
{
}


static char *itod(int allowed_dir)
{
    static char dir[5] = { 0 };
    int cpt = 0;

#define  ALLOWED_DIR(_dir)                                                   \
    if (allowed_dir & DIRECTION_##_dir) {                                    \
        dir[cpt++] = #_dir[0];                                               \
    }

    ALLOWED_DIR(N);
    ALLOWED_DIR(O);
    ALLOWED_DIR(S);
    ALLOWED_DIR(E);
    dir[cpt] = 0;
    return dir;
}

Action *TermPlayer::getAction(void)
{
    return NULL;
}

direction_t TermPlayer::selectMove(int allowed_dir)
{
    char str[255];

    std::cout << "Choose a direction to move [" << itod(allowed_dir)
              << "]" << std::endl;

    std::cin.getline(str, 255);
    while ((str[0] != 'N' && str[0] != 'O' && str[0] != 'S' && str[0] != 'E')
    ||      str[1])
    {
        std::cout << "Only enter one between [" << itod(allowed_dir)
                  << "] please" << std::endl;
        std::cin.getline(str, 255);
    }
    switch (str[0]) {
      case 'N':
        return DIRECTION_N;
      case 'O':
        return DIRECTION_O;
      case 'S':
        return DIRECTION_S;
      case 'E':
        return DIRECTION_E;
      default:
        assert (false);
    }
    return DIRECTION_N;
}

direction_t TermPlayer::selectSlide(int allowed_dir)
{
    char str[255];

    std::cout << "Choose a direction to slide [" << itod(allowed_dir)
              << "]" << std::endl;

    std::cin.getline(str, 255);
    while ((str[0] != 'N' && str[0] != 'O' && str[0] != 'S' && str[0] != 'E')
    ||      str[1])
    {
        std::cout << "Only enter one between [" << itod(allowed_dir)
                  << "] please" << std::endl;
        std::cin.getline(str, 255);
    }
    switch (str[0]) {
      case 'N':
        return DIRECTION_N;
      case 'O':
        return DIRECTION_O;
      case 'S':
        return DIRECTION_S;
      case 'E':
        return DIRECTION_E;
      default:
        assert (false);
    }
    return DIRECTION_N;
}


direction_t TermPlayer::selectSee(int allowed_dir)
{
    char str[255];

    std::cout << "Choose a direction to see [" << itod(allowed_dir)
              << "]" << std::endl;

    std::cin.getline(str, 255);
    while ((str[0] != 'N' && str[0] != 'O' && str[0] != 'S' && str[0] != 'E')
    ||      str[1])
    {
        std::cout << "Only enter one between [" << itod(allowed_dir)
                  << "] please" << std::endl;
        std::cin.getline(str, 255);
    }
    switch (str[0]) {
      case 'N':
        return DIRECTION_N;
      case 'O':
        return DIRECTION_O;
      case 'S':
        return DIRECTION_S;
      case 'E':
        return DIRECTION_E;
      default:
        assert (false);
    }
    return DIRECTION_N;
}

direction_t TermPlayer::selectPushDirection(int allowed_dir)
{
    char str[255];

    std::cout << "Choose a direction to push [" << itod(allowed_dir)
              << "]" << std::endl;

    std::cin.getline(str, 255);
    while ((str[0] != 'N' && str[0] != 'O' && str[0] != 'S' && str[0] != 'E')
    ||      str[1])
    {
        std::cout << "Only enter one between [" << itod(allowed_dir)
                  << "] please" << std::endl;
        std::cin.getline(str, 255);
    }
    switch (str[0]) {
      case 'N':
        return DIRECTION_N;
      case 'O':
        return DIRECTION_O;
      case 'S':
        return DIRECTION_S;
      case 'E':
        return DIRECTION_E;
      default:
        assert (false);
    }
    return DIRECTION_N;
}

Avatar *TermPlayer::selectPushTarget(std::vector<Avatar *> players)
{
    return players.front();
}


void TermPlayer::seeRoom(const Room *room)
{
    std::cout << "I see a room ";
    room->getEffect()->print(std::cout);
    std::cout << std::endl;
}
