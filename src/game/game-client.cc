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
#include "network/network.hh"

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
    Message *msg;

    this->rule = rule;
    this->board = this->rule->init_board();
    //rule->setTurn(nbTurn);

    //Connect to the server
    Network::getInstance()->client_connect("127.0.0.1", 5000);

    //wait(RULES)
    //init empty board
    //While wait(BOARD), change board rooms one by one

    //Send players to the server
    //At this point, all the local players are only true local players
    //Just send them to the server
    //Forall players, tell server

    return 0;
}

void GameClient::play_turn(void)
{
}


int GameClient::recv_msg()
{
    /*net_msg_t msg;
    int code;
    Cell *cell;
    Player *player;
    Scheduling *scheduling;

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
        Log::print("GameClient") << "Cell:\n\tcoords: (" << msg.cell.coords.x
                                 << "," << msg.cell.coords.y << ")"
                                 << "\n\teffect:" << msg.cell.effect
                                 << "\n\tis_visible:" << msg.cell.is_visible
                                 << std::endl;

        this->board->getCell(msg.cell.coords.x, msg.cell.coords.y)
                   ->setRoom(RoomFactory::getRoom(msg.cell.effect));

        break;
      case REQ_UPDATE_CELL: //Test: Seems ok
        Log::print("GameClient") << "Recvd request REQ_UPDATE_CELL"
                                 << std::endl;
        Log::print("GameClient") << "Cell:\n\tcoords: (" << msg.cell.coords.x
                                 << "," << msg.cell.coords.y << ")"
                                 << "\n\teffect:" << msg.cell.effect
                                 << "\n\tis_visible:" << msg.cell.is_visible
                                 << std::endl;

        cell = this->board->getCell(msg.cell.coords.x, msg.cell.coords.y);

        std::cout << "cell (" << msg.cell.coords.x << ", "
                  << msg.cell.coords.y << ") = " << cell << std::endl;

        if (cell->getRoom()->isVisible() != !!(msg.cell.is_visible)) {
            cell->getRoom()->setVisible((bool)(msg.cell.is_visible));
        }
        break;
      case REQ_CREATE_PLAYER:
        Log::print("GameClient") << "Recvd request REQ_CREATE_PLAYER"
                                 << std::endl;
        Log::print("GameClient") << "Cell:\n\tcoords: (" << msg.player.coords.x
                                 << "," << msg.player.coords.y << ")"
                                 << "\n\tavatar kind:" << msg.player.avatar_kind
                                 << std::endl;

        player = (Player *) new TermPlayer(msg.player.id);

        switch (msg.player.avatar_kind) {
          case AVATAR_KIND_PRISONER:
            player->setAvatar(new Prisoner(player));
            break;
          case AVATAR_KIND_DEFAULT:
          default:
            break;
        }

        this->addPlayer(player);
        break;
      case REQ_GET_PLAYER:
        break;
      case REQ_UPDATE_PLAYER:
        Log::print("GameClient") << "Recvd request REQ_UPDATE_PLAYER"
                                 << std::endl;
        this->board->print(std::cout);
        break;
      case REQ_GET_SCHEDULING:
        Log::print("GameClient") << "Recvd request REQ_GET_SCHEDULING"
                                 << std::endl;
        Log::print("GameClient") << "Scheduling asked for player_id:"
                                 << msg.scheduling.player_id
                                 << std::endl;

        player = this->getPlayerById(msg.scheduling.player_id);
        if (!player) {
            Log::error("GameClient") << "No player with id"
                                     << msg.scheduling.player_id << std::endl;
            return -2;
        }

        scheduling = player->getScheduling();
        msg.scheduling = scheduling->toNetScheduling();
        msg.req = REQ_SET_SCHEDULING;
        write(this->sock_fd, &msg, sizeof(msg));
        break;
      case REQ_GET_ACTION:
        Log::print("GameClient") << "Recvd request REQ_GET_CHOICE"
                                 << std::endl;
        // Think more about how to handle this (review net struct, ...)
        break;
      case REQ_FWD_ACTION: // EXEC ? FWD ?
        break;
      case REQ_RULES:
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
        }*/
    return 1;
}

int GameClient::send(net_msg_t msg)
{
}
