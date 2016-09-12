#include <iostream>
#include "utils/Log.hh"
#include "game/game.hh"
#include "game/game-client.hh"
#include "game/standard-rule.hh"
#include "player/term-player.hh"
#include "player/prisoner.hh"

int main(int argc, char **argv)
{
    Rule *rule;
    //Game *game = Game::getInstance();

    //game->init_game(new StandardRule(), 4, 10);

    GameClient *game = static_cast<GameClient *>(GameClient::getInstance());

    game->init_game(new StandardRule(), "127.0.0.1", 5000);
    /* rule = game->getRule(); */
    /* if (rule->manage_game()) { */
    /*     std::cout << "Whoa you win" << std::endl; */
    /* } */

    return 0;
}
