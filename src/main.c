#include <iostream>
#include "game/game.hh"


int main(int argc, char **argv)
{
    Player *player = NULL;
    Game *game = Game::getInstance();
    Board *board = game->getBoard();
    Move move;
    Slide slide;

    player = board->getCell(2, 2)->getRoom()->getPlayers().front();
    move.setOwner(player);
    slide.setOwner(player);

    std::cout << "initial" << std::endl;
    board->print(std::cout);
    std::cout << std::endl;

    std::cout << "move" << std::endl;
    game->exec(&move);
    board->print(std::cout);
    std::cout << std::endl;

    std::cout << "slide" << std::endl;
    game->exec(&slide);
    board->print(std::cout);
    std::cout << std::endl;

    std::cout << "move" << std::endl;
    game->exec(&move);
    board->print(std::cout);
    std::cout << std::endl;

    std::cout << "move" << std::endl;
    game->exec(&move);
    board->print(std::cout);
    std::cout << std::endl;

    std::cout << "move" << std::endl;
    game->exec(&move);
    board->print(std::cout);
    std::cout << std::endl;

    std::cout << "slide * 2" << std::endl;
    game->exec(&slide);
    game->exec(&slide);
    board->print(std::cout);

    return 0;
}
