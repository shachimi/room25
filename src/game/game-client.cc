#include "game/game-client.hh"
#include "utils/Log.hh"
#include "player/term-player.hh"
#include "network/enum.hh"

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

int GameClient::init_game(Rule *rule, char *server_address, int port)
{
    struct sockaddr_in serv_addr;

    this->rule = rule;

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

    while (this->recv()) { }

    //Recv game data from the server
    //Load board from server
    //this->board = this->rule->init_board();

    //Get number of turn from server
    //rule->setTurn(nb_turn);
    return 0;
}


int GameClient::recv()
{
    net_msg_t msg;
    int code;

    if (code = read(this->sock_fd, &msg, sizeof(msg)) < 0) {
        perror("[GameClient] error receiving message from server: ");
        return -1;
    } else if (code == 0) {
        Log::error("GameClient") << "Lost connection to the server"
                                 << std::endl;
        return 0;
    }

    switch (msg.req) {
      case REQ_CREATE_CELL:
      case REQ_UPDATE_CELL:
      case REQ_CREATE_PLAYER:
      case REQ_UPDATE_PLAYER:
      case REQ_GET_SCHEDULING:
      case REQ_GET_CHOICE:
      case REQ_EXEC_ACTION:
      default:
        Log::print("GameClient") << "Receiving req" << msg.req
                                 << "what should I do ?" << std::endl;
        break;
    }
    return 1;
}
