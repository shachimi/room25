#include <assert.h>
#include <vector>
#include "game.hh"
#include "utils/Log.hh"
#include "player/term-player.hh"

/* {{{ Initialize */

Game *Game::instance = NULL;

Game::Game(void)
    : players(std::vector<Player *>()),
      board(NULL),
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

void Game::init_game(Rule *rule, int nb_players, int nb_turn)
{
    this->rule = rule;
    this->board = this->rule->init_board();

    rule->setTurn(nb_turn);
    for (int i =0; i < nb_players; i++) {
        Player *p = (Player *) new TermPlayer(i + 1);

        p->setAvatar(new Prisoner(p));
        this->addPlayer(p);
    }
}

void Game::addPlayer(Player *player)
{
    this->players.push_back(player);
    if (this->board) {
        this->board->set_avatar_to_center(player->getAvatar());
    }
}

/* }}} */

void Game::play_turn(void)
{
    std::vector<Scheduling *> schedule = std::vector<Scheduling *>();

    /* All the players planify their actions */
    for (int i = 0; i < this->players.size(); i++) {
        Scheduling *scheduling;

        if (!this->players[i]->isAvatarAlive()) {
            schedule.push_back(NULL);
            continue;
        }

        Log::print() << "# Player" << this->players[i]->getId() << std::endl;

        scheduling = this->players[i]->getScheduling();
        assert (scheduling->isValid());
        schedule.push_back(scheduling);
    }

    Log::print() << "First programmation turn" << std::endl;
    for (int i = 0; i < schedule.size(); i++) {
        action_t action;

        if (!schedule[i]) {
            continue;
        }
        action = schedule[i]->getAction(1);

        Log::print() << "# Player" << schedule[i]->getOwner()->getId()
                     << std::endl;
        this->exec(action, schedule[i]->getOwner());
    }

    Log::print() << "Second programmation turn" << std::endl;
    for (int i = 0; i < schedule.size(); i++) {
        action_t action;

        if (!schedule[i]) {
            continue;
        }
        action = schedule[i]->getAction(2);

        Log::print() << "# Player" << schedule[i]->getOwner()->getId() << std::endl;
        this->exec(action, schedule[i]->getOwner());
    }
    for (int i = 0; i < schedule.size(); i++) {
        delete schedule[i];
        schedule[i] = NULL;
    }
    this->ends_turn();
}

void Game::ends_turn(void)
{
    std::vector<Cell *> cells = this->board->getCells();

    for (int i = 0; i < cells.size(); i++) {
        if (cells[i]->getRoom()->isVisible()) {
            cells[i]->getRoom()->getEffect()->turn_ends();
        }
    }

}

/* {{{ Execution of action */

void Game::exec(action_t action, Player *player)
{
    Avatar *avatar = player->getAvatar();

    /* TODO: validate the action */
    switch (action) {
      case ACTION_MOVE:
        this->execMove(player);
        break;
      case ACTION_PUSH:
        this->execPush(player);
        break;
      case ACTION_SLIDE:
        this->execSlide(player);
        break;
      case ACTION_SEE:
        this->execSee(player);
        break;
      case ACTION_NONE:
        break;
      default:
        assert (false && "should only be one action");
        break;
    }
}

void Game::execMove(Player *owner)
{
    direction_t dir;
    int allowed_dir = 0;
    Room *previous_room = owner->getAvatarRoom();
    Cell *cell = previous_room->getCell();

    if (cell->getLeft() && cell->getLeft()->getRoom()->isAccessible()) {
        allowed_dir |= DIRECTION_O;
    }
    if (cell->getRight() && cell->getRight()->getRoom()->isAccessible()) {
        allowed_dir |= DIRECTION_E;
    }
    if (cell->getUp() && cell->getUp()->getRoom()->isAccessible()) {
        allowed_dir |= DIRECTION_N;
    }
    if (cell->getDown() && cell->getDown()->getRoom()->isAccessible()) {
        allowed_dir |= DIRECTION_S;
    }
    if (!allowed_dir) {
        std::cerr << "nowhere to move" << std::endl;
        return;
    }

    dir = owner->selectMove(allowed_dir);
    /* TODO: do not assert */
    assert (dir & allowed_dir);
    this->board->move(owner, dir);
    previous_room->getEffect()->prisoner_leave(owner->getAvatar());
    owner->getAvatarRoom()->getEffect()->prisoner_enter(owner->getAvatar(),
                                                        previous_room->getCell());
}

void Game::execPush(Player *player)
{
    direction_t dir;
    int allowed_dir = 0;
    Avatar *victim = NULL;
    Cell *cell = player->getAvatar()->getRoom()->getCell();
    std::vector<Avatar *> targets = player->getAvatar()->getRoom()->getAvatars();

    if (cell->getRoom()->getEffect()->getKind() == ROOM_KIND_CENTER) {
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
    if (cell->getLeft() && cell->getLeft()->getRoom()->isAccessible()) {
        allowed_dir |= DIRECTION_O;
    }
    if (cell->getRight() && cell->getRight()->getRoom()->isAccessible()) {
        allowed_dir |= DIRECTION_E;
    }
    if (cell->getUp() && cell->getUp()->getRoom()->isAccessible()) {
        allowed_dir |= DIRECTION_N;
    }
    if (cell->getDown() && cell->getDown()->getRoom()->isAccessible()) {
        allowed_dir |= DIRECTION_S;
    }
    if (!allowed_dir) {
        std::cerr << "nowhere to push" << std::endl;
        return;
    }
    dir = player->selectPushDirection(allowed_dir);

    victim = player->selectPushTarget(targets);
    this->board->push(player, victim, dir);

    /* resolve effects */
    player->getAvatarRoom()->getEffect()->prisoner_leave(victim);
    victim->getRoom()->getEffect()->prisoner_enter(victim,
                                                   player->getAvatarRoom()->getCell());
    player->getAvatarRoom()->getEffect()->prisoner_stay(player->getAvatar());
}

void Game::execSee(Player *player)
{
    room_kind_t saw;
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
    saw = this->board->see(player, dir);

    /* tell the others */
    for (int i = 0; i < this->players.size(); i++) {
        if (this->players[i] != player) {
            this->players[i]->roomSaw(player, saw);
        }
    }

    /* resolve effects */
    player->getAvatarRoom()->getEffect()->prisoner_stay(player->getAvatar());
}

bool Game::checkWin(int pos, direction_t dir)
{
    int x = pos % this->board->getL();
    int y = pos / this->board->getL();

    if ((x != 0 && x != this->board->getL())
    ||  (y != 0 && y != this->board->getL()))
    {
        return false;
    }

    /* two way of exit:
     *    - But first is there key?
     *    - Second:
     *         - Last turn and only one dead
     *         - everybody on it
     */
    return this->board->getCell(pos)->getRoomKind() == ROOM_KIND_EXIT
        && ((dir == DIRECTION_N && y == 0)
        ||  (dir == DIRECTION_O && x == 0)
        ||  (dir == DIRECTION_S && y == this->board->getL())
        ||  (dir == DIRECTION_E && x == this->board->getL()))
        && this->rule->checkWinningCond(pos);
}

void Game::execSlide(Player *player)
{
    direction_t dir;
    int allowed_dir = 0;
    int pos = player->getAvatar()->getRoom()->getCell()->getPos();

    /* XXX: better than looking for the center room in the line */
    if (pos % 5 /* x */ != this->board->getL() / 2) {
        if (this->board->getCell(pos)->getSlideDirs() & DIRECTION_S) {
            allowed_dir |= DIRECTION_S;
        } else
        if (this->board->getCell(pos)->getSlideDirs() & DIRECTION_N) {
            allowed_dir |= DIRECTION_N;
        } else {
            allowed_dir |= DIRECTION_N | DIRECTION_S;
        }
    }
    if (pos / 5 /* y */ != this->board->getL() / 2) {
        if (this->board->getCell(pos)->getSlideDirs() & DIRECTION_O) {
            allowed_dir |= DIRECTION_O;
        } else
        if (this->board->getCell(pos)->getSlideDirs() & DIRECTION_E) {
            allowed_dir |= DIRECTION_E;
        } else {
            allowed_dir |= DIRECTION_E | DIRECTION_O;
        }
    }

    if (!allowed_dir) {
        std::cerr << "you cannot slide in this cell" << std::endl;
        return;
    }
    dir = player->selectSlide(allowed_dir);
    /* TODO: do not assert */
    assert (dir & allowed_dir);

    if (this->checkWin(pos, dir) && player->goOutComplex()) {
        throw true;
    }

    this->board->slide(player, dir);
    /* resolve effects */
    player->getAvatarRoom()->getEffect()->prisoner_stay(player->getAvatar());
}

/* }}} */
/* {{{ Management board */

void Game::removeAvatar(Avatar *avatar)
{
    Prisoner *prisoner = static_cast<Prisoner *>(avatar);

    if (prisoner && this->rule->destroyPrisoner(prisoner)) {
        throw "Game Over";
        /* TODO: do agraceful exit rather than this. */
    }
}

void Game::rotatePlayer(void)
{
    /* TODO: replace players.size by the number total of prisoner in case
     *       one is player control several prisoner
     */
    do {
        this->first_player = (this->first_player + 1) % this->players.size();
    } while (!this->players[this->first_player]->isAvatarAlive());
}


/* }}} */
