#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#include "game/game-client.hh"
#include "utils/Log.hh"
#include "player/term-player.hh"
#include "board/room-factory.hh"

/*
TODO
- Redefine init_game
    Game::init_game
    initialize
        sock_fd
        serv_addr using the right port
        the board (from the server)
        the players (from the server)

- Redefine play_turn
    wait for server message and execute the corresponding action
    loop while !recvd end_of_turn

 */

GameClient::GameClient(void)
    : Game(),
      sock_fd(0)
{
}

GameClient::~GameClient(void)
{
}

Game *GameClient::getInstance(void)
{
    if (!Game::instance) {
        Game::instance = new GameClient();
    }

    return GameClient::instance;
}

int GameClient::init_game(Rule *rule, char *server_address, int port)
{
    struct sockaddr_in serv_addr;

    this->rule = rule;
    this->board = new Board();

    //Connect to the server
    if ((this->sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("[GameClient] Error creating socket: ");
        return -1;
    }
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, server_address, &serv_addr.sin_addr) <= 0) {
        perror("[GameClient] inet_pton error: ");
        return -1;
    }
    if (connect(this->sock_fd, (struct sockaddr *)&serv_addr,
                sizeof(serv_addr)) < 0)
    {
        perror("[GameClient] Couldn't connect to the server: ");
        return -1;
    }
    Log::print("GameClient") << "Connected to the server ." << this->sock_fd << std::endl;

    while (this->recv_msg()) { }

    //Recv game data from the server
    //Load board from server
    //this->board = this->rule->init_board();

    //Get number of turn from server
    //rule->setTurn(nb_turn);
    return 0;
}

void GameClient::play_turn(void)
{
}


int GameClient::recv_msg()
{
    net_msg_t msg;
    int code;
    Cell *cell;

    if ((code = read(this->sock_fd, &msg, sizeof(msg))) < 0) {
        perror("[GameClient] error receiving message from server: ");
        return -1;
    } else if (code == 0) {
        Log::error("GameClient") << "Lost connection to the server"
                                 << std::endl;
        return 0;
    }

    switch (msg.req) {
      case REQ_CREATE_CELL: //Test: Seems ok
        Log::print("GameClient") << "Recvd request REQ_CREATE_CELL"
                                 << std::endl;
        Log::print("GameClient") << "Cell:\n\tid:" << msg.cell.id
                                 << "\n\tcoords: (" << msg.cell.coords.x
                                 << "," << msg.cell.coords.y << ")"
                                 << "\n\teffect:" << msg.cell.effect
                                 << "\n\tis_visible:" << msg.cell.is_visible
                                 << std::endl;

        this->board->setCell(msg.cell.coords.x, msg.cell.coords.y,
                             new Cell(msg.cell.id,
                                 this->board->getPos(msg.cell.coords.x,
                                                     msg.cell.coords.y),
                                 RoomFactory::getRoom(msg.cell.effect)));

        break;
      case REQ_UPDATE_CELL: //Test: Seems ok
        Log::print("GameClient") << "Recvd request REQ_UPDATE_CELL"
                                 << std::endl;
        Log::print("GameClient") << "Cell:\n\tid:" << msg.cell.id
                                 << "\n\tcoords: (" << msg.cell.coords.x
                                 << "," << msg.cell.coords.y << ")"
                                 << "\n\teffect:" << msg.cell.effect
                                 << "\n\tis_visible:" << msg.cell.is_visible
                                 << std::endl;

        cell = this->board->getCellById(msg.cell.id);

        if (cell->getX() != msg.cell.coords.x
            || cell->getY() != msg.cell.coords.y)
        {
            cell->setPos(this->board->getPos(msg.cell.coords.x,
                                            msg.cell.coords.y));
        }

        if (cell->getRoom()->isVisible() != !!(msg.cell.is_visible)) {
            cell->getRoom()->setVisible((bool)(msg.cell.is_visible));
        }
        break;
      case REQ_CREATE_PLAYER:
        break;
      case REQ_GET_PLAYER:
        break;
      case REQ_UPDATE_PLAYER:
        Log::print("GameClient") << "Recvd request REQ_UPDATE_PLAYER"
                                 << std::endl;
        this->board->print(std::cout);
        break;
      case REQ_GET_SCHEDULING: //Needs REQ_CREATE_PLAYER
        break;
      case REQ_GET_CHOICE: //Needs REQ_CREATE_PLAYER
        break;
      case REQ_EXEC_ACTION:
        break;
      case REQ_SET_RULES:
        Log::print("GameClient") << "Recvd request REQ_SET_RULES"
                                 << std::endl;
        Log::print("GameClient") << "Rules:\n"
                                 << "\n\tnb_turn:" << msg.rules.nb_turn
                                 << std::endl;

        this->rule->setTurn(msg.rules.nb_turn);
        break;
      default:
        Log::print("GameClient") << "Receiving unknown request: " << msg.req
                                 << std::endl;
        break;
    }
    return 1;
}

int GameClient::send(net_msg_t msg)
{
}
