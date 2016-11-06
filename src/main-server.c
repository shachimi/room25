#include <iostream>
#include "game/game.hh"
#include "game/game-server.hh"
#include "game/standard-rule.hh"

int main(int argc, char **argv)
{
    Rule *rule;
    //Game *game = Game::getInstance();

    //game->init_game(new StandardRule(), 4, 10);

    GameServer *game = static_cast<GameServer *>(GameServer::getInstance());

    game->init_game(new StandardRule(), 1, 10, "127.0.0.1", 5000);
    /* rule = game->getRule(); */
    /* if (rule->manage_game()) { */
    /*     std::cout << "Whoa you win" << std::endl; */
    /* } */

    return 0;
}
