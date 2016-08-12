#include <iostream>
#include "game/game.hh"


int main(int argc, char **argv)
{
    Player *player = NULL;
    Game *game = Game::getInstance();
    Board *board = game->getBoard();
    Move move;

    board->print(std::cout);
    std::cout << std::endl << std::endl;
    std::cout << "Slide (1, 1) N" << std::endl;
    board->slide(0, 0, DIRECTION_N);
    board->print(std::cout);
    std::cout << std::endl << std::endl;
    std::cout << "Slide (2, 4) E" << std::endl;
    board->slide(1, 3, DIRECTION_E);
    board->print(std::cout);
    std::cout << std::endl << std::endl;
    std::cout << "Slide (4, 3) S * 3" << std::endl;
    board->slide(3, 2, DIRECTION_S);
    board->slide(3, 2, DIRECTION_S);
    board->slide(3, 2, DIRECTION_S);
    board->print(std::cout);
    std::cout << "Slide (4, 3) O" << std::endl;
    board->slide(3, 2, DIRECTION_O);


    player = board->getCell(2, 2)->getRoom()->getPlayers().front();
    move.setOwner(player);
    board->move(player, DIRECTION_E);
    game->exec(&move);
    game->exec(&move);
    game->exec(&move);
    game->exec(&move);
    game->exec(&move);
    game->exec(&move);
    game->exec(&move);
    game->exec(&move);
    game->exec(&move);
    game->exec(&move);

    board->print(std::cout);
    return 0;
}
