#include <assert.h>
#include <vector>
#include "game.hh"
#include "utils/Log.hh"

/* {{{ Initialize */

Game *Game::instance = NULL;

Game::Game(void)
    : players(std::vector<Player *>()),
      board(new Board()),
      rule(NULL),
      first_player(0)
{
}

Game::~Game(void)
{
}

Game *Game::getInstance(void)
{
    if (!Game::instance) {
        Game::instance = new Game();
    }
    return Game::instance;
}

/* }}} */

void Game::play_turn(void)
{
    std::vector<Scheduling *> schedule = std::vector<Scheduling *>();

    /* All the players planify their actions */
    for (int i = this->first_player;
         i < this->players.size() + this->first_player; i++)
    {
        Scheduling *scheduling;
        Player *player = this->players[i % this->players.size()];

        Log::print() << "# Player" << player->getId();

        scheduling = this->players[i]->getScheduling();
        assert (scheduling->isValid());
        schedule.push_back(scheduling);
    }

    Log::print() << "First programmation turn" << std::endl;
    for (int i = 0; i < schedule.size(); i++) {
        action_t action = schedule[i]->getAction(1);

        Log::print() << "# Player" << schedule[i]->getOwner()->getId();
        switch (action) {
          case ACTION_MOVE:
            this->execMove(schedule[i]->getOwner());
            break;
          case ACTION_PUSH:
            this->execPush(schedule[i]->getOwner());
            break;
          case ACTION_SLIDE:
            this->execSlide(schedule[i]->getOwner());
            break;
          case ACTION_SEE:
            this->execSee(schedule[i]->getOwner());
            break;
          case ACTION_NONE:
            break;
          default:
            assert (false && "should only be one action");
            break;
        }
    }

    Log::print() << "Second programmation turn" << std::endl;
    for (int i = 0; i < schedule.size(); i++) {
        action_t action = schedule[i]->getAction(2);

        Log::print() << "# Player" << schedule[i]->getOwner()->getId();
        switch (action) {
          case ACTION_MOVE:
            this->execMove(schedule[i]->getOwner());
            break;
          case ACTION_PUSH:
            this->execPush(schedule[i]->getOwner());
            break;
          case ACTION_SLIDE:
            this->execSlide(schedule[i]->getOwner());
            break;
          case ACTION_SEE:
            this->execSee(schedule[i]->getOwner());
            break;
          case ACTION_NONE:
            break;
          default:
            assert (false && "should only be one action");
            break;
        }
    }
    for (int i = 0; i < schedule.size(); i++) {
        delete schedule[i];
        schedule[i] = NULL;
    }
}

/* {{{ Execution of action */

void Game::exec(Action *action)
{
    std::cerr << "not implemented yet" << std::endl;
}

void Game::execMove(Player *owner)
{
    direction_t dir;
    int allowed_dir = 0;
    int pos = owner->getAvatar()->getRoom()->getCell()->getPos();

    if (pos % 5 /* x */ > 0) {
        allowed_dir |= DIRECTION_O;
    }
    if (pos % 5 /* x */ < 4) {
        allowed_dir |= DIRECTION_E;
    }
    if (pos / 5 /* y */ > 0) {
        allowed_dir |= DIRECTION_N;
    }
    if (pos / 5 /* y */ < 4) {
        allowed_dir |= DIRECTION_S;
    }
    dir = owner->selectMove(allowed_dir);
    /* TODO: do not assert */
    assert (dir & allowed_dir);
    this->board->move(owner, dir);
}

void Game::execPush(Player *player)
{
    direction_t dir;
    int allowed_dir = 0;
    int pos = player->getAvatar()->getRoom()->getCell()->getPos();
    std::vector<Avatar *> targets = player->getAvatar()->getRoom()->getAvatars();

    if (pos == 12) {
        /* TODO: replace by validateAction of center room (rename secure?) */
        std::cerr << "cannot push from center room" << std::endl;
        return;
    }

    {
        std::vector<Avatar *>::iterator it;

        for (it = targets.begin() ; it != targets.end(); ++it) {
            if (*it == player->getAvatar()) {
                targets.erase(it);
                break;
            }
        }
    }

    if (!targets.size()) {
        std::cerr << "nobody to push" << std::endl;
        return;
    }
    if (pos % 5 /* x */ > 0) {
        allowed_dir |= DIRECTION_O;
    }
    if (pos % 5 /* x */ < 4) {
        allowed_dir |= DIRECTION_E;
    }
    if (pos / 5 /* y */ > 0) {
        allowed_dir |= DIRECTION_N;
    }
    if (pos / 5 /* y */ < 4) {
        allowed_dir |= DIRECTION_S;
    }
    dir = player->selectPushDirection(allowed_dir);

    /* TODO: do not assert */
    assert (dir & allowed_dir);
    this->board->push(player, player->selectPushTarget(targets), dir);
}

void Game::execSee(Player *player)
{
    direction_t dir;
    int allowed_dir = 0;
    Cell *cell = player->getAvatar()->getRoom()->getCell();

    if (cell->getLeft() && !cell->getLeft()->getRoom()->isVisible()) {
        allowed_dir |= DIRECTION_O;
    }
    if (cell->getRight() && !cell->getRight()->getRoom()->isVisible()) {
        allowed_dir |= DIRECTION_E;
    }
    if (cell->getUp() && !cell->getUp()->getRoom()->isVisible()) {
        allowed_dir |= DIRECTION_N;
    }
    if (cell->getDown() && !cell->getDown()->getRoom()->isVisible()) {
        allowed_dir |= DIRECTION_S;
    }
    dir = player->selectSee(allowed_dir);
    if (!allowed_dir) {
        std::cerr << "nothing to see here" << std::endl;
        return;
    }
    /* TODO: do not assert */
    assert (dir & allowed_dir);
    this->board->see(player, dir);
}

void Game::execSlide(Player *player)
{
    direction_t dir;
    int allowed_dir = 0;
    int pos = player->getAvatar()->getRoom()->getCell()->getPos();

    if (pos % 5 /* x */ != 2) {
        allowed_dir |= DIRECTION_N | DIRECTION_S;
    }
    if (pos / 5 /* y */ != 2) {
        allowed_dir |= DIRECTION_O | DIRECTION_E;
    }

    if (!allowed_dir) {
        std::cerr << "you cannot slide in this cell" << std::endl;
        return;
    }
    dir = player->selectSlide(allowed_dir);
    /* TODO: do not assert */
    assert (dir & allowed_dir);
    this->board->slide(player, dir);
}

/* }}} */
/* {{{ Management board */

void Game::removeAvatar(Avatar *avatar)
{
    Prisoner *prisoner = static_cast<Prisoner *>(avatar);

    avatar->destroy();
    if (prisoner && this->rule->destroyPrisoner(prisoner)) {
        Log::print() << "GAME OVER";
        /* TODO: do agraceful exit rather than this. */
        // exit(0);
    }
}

void Game::rotatePlayer(void)
{
    /* TODO: replace players.size by the number total of prisoner in case
     *       one is player control several prisoner
     */
    this->first_player = (this->first_player + 1) % this->players.size();
}


/* }}} */
