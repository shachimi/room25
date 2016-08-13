#include "game.hh"
#include <assert.h>

Game *Game::instance = NULL;

Game::Game(void)
    : players(std::queue<Player *>()),
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
}

/* {{{ Execution of action */

void Game::exec(Action *action)
{
    std::cerr << "not implemented yet" << std::endl;
}

void Game::exec(Move *move)
{
    direction_t dir;
    int allowed_dir = 0;
    int pos = move->getOwner()->getRoom()->getCell()->getPos();

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
    dir = move->getOwner()->execMove(allowed_dir);
    /* TODO: do not assert */
    assert (dir & allowed_dir);
    this->board->move(move->getOwner(), dir);
}

void Game::exec(Slide *slide)
{
    direction_t dir;
    int allowed_dir = 0;
    int pos = slide->getOwner()->getRoom()->getCell()->getPos();

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
    dir = slide->getOwner()->execSlide(allowed_dir);
    /* TODO: do not assert */
    assert (dir & allowed_dir);
    this->board->slide(slide->getOwner(), dir);
}

/* }}} */

void Game::rotatePlayer(void)
{
    Player *tmp = this->players.front();

    this->players.pop();
    this->players.push(tmp);
}
