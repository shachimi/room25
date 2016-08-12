#include "./games.hh"

Game::Game(void)
{
}

Game::~Game(void)
{
}

void Game::play_turn(void)
{
}

void Game::exec(Action * action)
{
}


void Game::rotatePlayer(void)
{
    Player *tmp = this->players.front();

    this->players.pop();
    this->players.push(tmp);
}
