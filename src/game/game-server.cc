#include "game/game-server.hh"
#include "utils/Log.hh"
#include "player/term-player.hh"
#include "board/room-factory.hh"

GameServer::GameServer(void)
    : Game(),
      sock_fd(0)
{
}

GameServer::~GameServer(void)
{
}

Game *GameServer::getInstance(void)
{
    if (!Game::instance) {
        Game::instance = new GameServer();
    }

    return GameServer::instance;
}

int GameServer::init_game(Rule *rule, char *server_address, int port)
{
}

void GameServer::play_turn(void)
{
}
