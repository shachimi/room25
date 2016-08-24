#include <assert.h>
#include <vector>
#include "game.hh"
#include "utils/Log.h"

Game *Game::instance = NULL;

Game::Game(void)
    : players(std::vector<Player *>()),
      board(new Board())
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

void Game::play_turn(void)
{
    std::vector<Scheduling *> schedule = std::vector<Scheduling *>();

	//All the players planify their actions
    for (int i = 0; i < this->players.size(); i++) {
        Scheduling *scheduling = this->players[i]->getScheduling();

        assert (scheduling->isValid());
        schedule.push_back(scheduling);
    }

	Log::print() << "First programmation turn" << std::endl;
    for (int i = 0; i < schedule.size(); i++) {
        action_t action = schedule[i]->getAction(1);

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
    /* TODO: remove the robot and see what to do with prisoner */
}

void Game::rotatePlayer(void)
{
    // Player *tmp = this->players.front();

    // this->players.pop();
    // this->players.push(tmp);
}


/* }}} */
