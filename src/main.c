#include <iostream>
#include "room/board.hh"


int main(int argc, char **argv)
{
    Player *player = NULL;
    Board *board = new Board();

    board->print(std::cout);
    std::cout << std::endl << std::endl;
    board->slide(0, 0, DIRECTION_N);
    board->print(std::cout);
    std::cout << std::endl << std::endl;
    board->slide(0, 1, DIRECTION_E);
    board->print(std::cout);
    std::cout << std::endl << std::endl;
    board->slide(3, 2, DIRECTION_S);
    board->slide(3, 2, DIRECTION_S);
    board->slide(3, 2, DIRECTION_S);
    board->print(std::cout);
    board->slide(3, 2, DIRECTION_O);


    player = board->getCell(2, 2)->getRoom()->getPlayers().front();
    board->move(player, DIRECTION_E);
    board->move(player, DIRECTION_N);
    board->move(player, DIRECTION_N);
    board->move(player, DIRECTION_O);
    board->move(player, DIRECTION_O);
    board->move(player, DIRECTION_O);
    board->move(player, DIRECTION_S);

    board->print(std::cout);
    return 0;
}
