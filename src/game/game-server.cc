#include "game/game-server.hh"
#include "utils/Log.hh"
#include "player/distant-player.hh"
#include "board/room-factory.hh"
#include "player/avatar-factory.hh"

GameServer::GameServer(void)
    : Game(),
      sock_fd(0),
      clients(std::vector<int>())
{
}

GameServer::~GameServer(void)
{
}

Game *GameServer::getInstance(void)
{
    if (!Game::instance) {
        Game::instance = new GameServer();
    }

    return GameServer::instance;
}

int GameServer::init_game(Rule *rule, int nb_clients, int nb_turn, char *server_address, int port)
{
    Message *msg;
    int nb_clients_to_accept = 2;
    int sock;

    this->rule = rule;
    this->board = this->rule->init_board();
    // rule->setTurn(nb_turn);

    // Open server
    Network::getInstance()->server_open(5000);

    // Get connection to the clients
    for (int i = 0; i < nb_clients_to_accept; i++) {
        this->clients.push_back(
            Network::getInstance()->server_accept());
    }

    for (int i = 0; i < this->clients.size(); i++) {
        PlayerMsg *msg;
        while ((msg = static_cast<PlayerMsg *>(
                    Network::getInstance()->wait(
                        REQ_PLAYER, this->clients[i]))) != NULL)
        {
            DistantPlayer *p = new DistantPlayer(1);
            p->setId(msg->getId());
            p->setCell(Game::getInstance()->getBoard()->getCenterCell());
            p->setAvatar(AvatarFactory::getAvatar(msg->getAvatarKind()));
            p->setSock(this->clients[i]);
            // delete msg ?
        }
    }
}

void GameServer::play_turn(void)
{
}
