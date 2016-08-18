#include <iostream>
#include "game/game.hh"
#include "player/term-player.hh"
#include "player/prisoner.hh"


int main(int argc, char **argv)
{
    Player *p1 = (Player *) new TermPlayer(1);
    Player *p2 = (Player *) new TermPlayer(2);
    Game *game = Game::getInstance();
    Board *board = game->getBoard();

    p1->setAvatar(new Prisoner(p1));
    p2->setAvatar(new Prisoner(p2));
    board->getCell(2, 2)->getRoom()->addAvatar(p1->getAvatar(), false);
    board->getCell(2, 2)->getRoom()->addAvatar(p2->getAvatar(), false);
    game->pushPlayer(p1);
    game->pushPlayer(p2);

    std::cout << "Turn 1" << std::endl;
    game->play_turn();
    board->print(std::cout);
    std::cout << "Turn 2" << std::endl;
    game->play_turn();
    board->print(std::cout);
    std::cout << "Turn 3" << std::endl;
    game->play_turn();
    board->print(std::cout);
    std::cout << "Turn 4" << std::endl;
    game->play_turn();
    board->print(std::cout);
    std::cout << "Turn 5" << std::endl;
    game->play_turn();
    board->print(std::cout);

    return 0;
}
