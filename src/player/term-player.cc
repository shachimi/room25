#include "term-player.hh"
#include <assert.h>
#include "utils/Log.h"

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
#undef ALLOWED_DIR
    dir[cpt] = 0;
    return dir;
}

static char *action_available(char already_choose='\0')
{
    static char action[5] = { 0 };
    int cpt = 0;

#define  ALLOWED_ACTION(_action)                                             \
    if (already_choose != _action) {                                         \
        action[cpt++] = _action;                                             \
    }

    ALLOWED_ACTION('M');
    ALLOWED_ACTION('P');
    ALLOWED_ACTION('C');
    ALLOWED_ACTION('S');
#undef ALLOWED_ACTION
    action[cpt] = 0;
    return action;
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
    char *actions;
    Scheduling *scheduling = new Scheduling();

    scheduling->setOwner(this);
    actions = action_available();
    Log::print() << "Choose your first action [" << actions << "]" << std::endl;
    std::cin.getline(str, 255);
    while ((str[0] != 'M' && str[0] != 'S' && str[0] != 'P' && str[0] != 'C')
    ||      str[1])
    {
        Log::print() << "Only enter one between [" << actions
			<< "] please" << std::endl;
        std::cin.getline(str, 255);
    }
    scheduling->setAction(get_action_from_command(str[0]), 1);
    actions = action_available(str[0]);

	Log::print() << "Choose your second action [" << actions
		<< "] or None(N)" << std::endl;
    std::cin.getline(str, 255);
    while ((str[0] != 'M' && str[0] != 'S' && str[0] != 'P' && str[0] != 'C' && str[0] != 'N')
    ||      str[1])
    {
		Log::print() << "Only enter one between [" << actions
			<< "] or N please" << std::endl;
        std::cin.getline(str, 255);
    }
    scheduling->setAction(get_action_from_command(str[0]), 2);

    return scheduling;
}

bool TermPlayer::useAction(void)
{
    char str[255];

	Log::print() << "Do you want to use your action [y/n]?" << std::endl;

    std::cin.getline(str, 255);
    while ((str[0] != 'y' && str[0] != 'Y' && str[0] != 'n' && str[0] != 'N')
    ||      str[1])
    {
		Log::print() << "Yes or No?" << std::endl;
        std::cin.getline(str, 255);
    }
    return str[0] == 'y' || str[0] == 'Y';
}

direction_t TermPlayer::selectMove(int allowed_dir)
{
    char str[255];

	Log::print() << "Choose a direction to move [" << itod(allowed_dir)
              << "]" << std::endl;

    std::cin.getline(str, 255);
    while ((str[0] != 'N' && str[0] != 'O' && str[0] != 'S' && str[0] != 'E')
    ||      str[1])
    {
		Log::print() << "Only enter one between [" << itod(allowed_dir)
                  << "] please" << std::endl;
        std::cin.getline(str, 255);
    }
    return get_direction_from_command(str[0]);
}

direction_t TermPlayer::selectSlide(int allowed_dir)
{
    char str[255];

	Log::print() << "Choose a direction to slide [" << itod(allowed_dir)
              << "]" << std::endl;

    std::cin.getline(str, 255);
    while ((str[0] != 'N' && str[0] != 'O' && str[0] != 'S' && str[0] != 'E')
    ||      str[1])
    {
		Log::print() << "Only enter one between [" << itod(allowed_dir)
                  << "] please" << std::endl;
        std::cin.getline(str, 255);
    }

    return get_direction_from_command(str[0]);
}


direction_t TermPlayer::selectSee(int allowed_dir)
{
    char str[255];

	Log::print() << "Choose a direction to see [" << itod(allowed_dir)
              << "]" << std::endl;

    std::cin.getline(str, 255);
    while ((str[0] != 'N' && str[0] != 'O' && str[0] != 'S' && str[0] != 'E')
    ||      str[1])
    {
		Log::print() << "Only enter one between [" << itod(allowed_dir)
                  << "] please" << std::endl;
        std::cin.getline(str, 255);
    }

    return get_direction_from_command(str[0]);
}

direction_t TermPlayer::selectPushDirection(int allowed_dir)
{
    char str[255];

	Log::print() << "Choose a direction to push [" << itod(allowed_dir)
              << "]" << std::endl;

    std::cin.getline(str, 255);
    while ((str[0] != 'N' && str[0] != 'O' && str[0] != 'S' && str[0] != 'E')
    ||      str[1])
    {
		Log::print() << "Only enter one between [" << itod(allowed_dir)
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
	Log::print() << "I see a room ";
    room->getEffect()->print(std::cout);
	Log::print() << std::endl;
}
