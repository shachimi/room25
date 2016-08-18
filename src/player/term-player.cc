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

static action_t get_action_from_command(char command)
{
    if (command == 'M') {
        return ACTION_MOVE;
    } else
    if (command == 'S') {
        return ACTION_SEE;
    } else
    if (command == 'P') {
        return ACTION_PUSH;
    } else
    if (command == 'C') {
        return ACTION_SLIDE;
    }
    assert (false);
    return ACTION_NONE;
}

static direction_t get_direction_from_command(char command)
{
    if (command == 'N') {
        return DIRECTION_N;
    } else
    if (command == 'O') {
        return DIRECTION_O;
    } else
    if (command == 'S') {
        return DIRECTION_S;
    } else
    if (command == 'E') {
        return DIRECTION_E;
    }
    assert (false);
    return DIRECTION_N;
}

Scheduling *TermPlayer::getScheduling(void)
{
    char str[255];
    Scheduling *scheduling = new Scheduling();

    scheduling->setOwner(this);
    std::cout << "Choose your first action [MSPC]" << std::endl;
    std::cin.getline(str, 255);
    while ((str[0] != 'M' && str[0] != 'S' && str[0] != 'P' && str[0] != 'C')
    ||      str[1])
    {
        std::cout << "Only enter one between [MSPC] please" << std::endl;
        std::cin.getline(str, 255);
    }
    scheduling->setAction(get_action_from_command(str[0]), 1);

    std::cout << "Choose your second action [MSPC]" << std::endl;
    std::cin.getline(str, 255);
    while ((str[0] != 'M' && str[0] != 'S' && str[0] != 'P' && str[0] != 'C')
    ||      str[1])
    {
        std::cout << "Only enter one between [MSPC] please" << std::endl;
        std::cin.getline(str, 255);
    }
    scheduling->setAction(get_action_from_command(str[0]), 2);

    return scheduling;
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
    return get_direction_from_command(str[0]);
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

    return get_direction_from_command(str[0]);
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

    return get_direction_from_command(str[0]);
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

    return get_direction_from_command(str[0]);
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
