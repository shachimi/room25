#include <iostream>
#include "game/game.hh"
#include "player/term-player.hh"
#include "player/avatar.hh"


int main(int argc, char **argv)
{
    Player *p1 = (Player *) new TermPlayer();
    Player *p2 = (Player *) new TermPlayer();
    Game *game = Game::getInstance();
    Board *board = game->getBoard();
    Move move1, move2;
    See see;
    Push push;
    Slide slide;

    p1->setAvatar(new Avatar());
    p2->setAvatar(new Avatar());
    board->getCell(2, 2)->getRoom()->addAvatar(p1->getAvatar(), false);
    board->getCell(2, 2)->getRoom()->addAvatar(p2->getAvatar(), false);
    move1.setOwner(p1);
    move2.setOwner(p2);
    slide.setOwner(p1);
    see.setOwner(p1);
    push.setOwner(p2);

    std::cout << "initial" << std::endl;
    board->print(std::cout);
    std::cout << std::endl;

    std::cout << "move1" << std::endl;
    game->exec(&move1);
    board->print(std::cout);
    std::cout << std::endl;

    std::cout << "move2" << std::endl;
    game->exec(&move2);
    board->print(std::cout);
    std::cout << std::endl;

    std::cout << "push" << std::endl;
    game->exec(&push);
    board->print(std::cout);
    std::cout << std::endl;

    std::cout << "see" << std::endl;
    game->exec(&see);
    board->print(std::cout);
    std::cout << std::endl;

    std::cout << "slide" << std::endl;
    game->exec(&slide);
    board->print(std::cout);
    std::cout << std::endl;

    std::cout << "move1" << std::endl;
    game->exec(&move1);
    board->print(std::cout);
    std::cout << std::endl;

    std::cout << "move1" << std::endl;
    game->exec(&move1);
    board->print(std::cout);
    std::cout << std::endl;

    std::cout << "slide * 2" << std::endl;
    game->exec(&slide);
    game->exec(&slide);
    board->print(std::cout);

    return 0;
}
