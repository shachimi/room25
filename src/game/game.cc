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
    dir = move->getOwner()->selectMove(allowed_dir);
    /* TODO: do not assert */
    assert (dir & allowed_dir);
    this->board->move(move->getOwner(), dir);
}

void Game::exec(Push *push)
{
    direction_t dir;
    int allowed_dir = 0;
    int pos = push->getOwner()->getRoom()->getCell()->getPos();
    std::vector<Player *> targets = push->getOwner()->getRoom()->getPlayers();

    if (pos == 12) {
        std::cerr << "cannot push from center room" << std::endl;
        return;
    }

    {
        std::vector<Player *>::iterator it;

        for (it = targets.begin() ; it != targets.end(); ++it) {
            if (*it == push->getOwner()) {
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
    dir = push->getOwner()->selectPushDirection(allowed_dir);

    /* TODO: do not assert */
    assert (dir & allowed_dir);
    this->board->push(push->getOwner(),
                      push->getOwner()->selectPushTarget(targets), dir);
}

void Game::exec(See *see)
{
    direction_t dir;
    int allowed_dir = 0;
    Cell *cell = see->getOwner()->getRoom()->getCell();

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
    dir = see->getOwner()->selectSee(allowed_dir);
    if (!allowed_dir) {
        std::cerr << "nothing to see here" << std::endl;
        return;
    }
    /* TODO: do not assert */
    assert (dir & allowed_dir);
    this->board->see(see->getOwner(), dir);
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
    dir = slide->getOwner()->selectSlide(allowed_dir);
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
