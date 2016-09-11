#include "server.hh"

Server::Server(void)
    : clients()
{
}

int Server::start(void)
{
    memset(&this->address, '0', sizeof(this->address));

    if ((this->listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("[Server] socket creation failed. Error: ");
        return -1;
    }

    this->address.sin_family = AF_INET;
    this->address.sin_addr.s_addr = htonl(INADDR_ANY);
    this->address.sin_port = htons(this->port);

    if (bind(this->listenfd, (struct sockaddr*)&this->address,
             sizeof(this->address)) < 0)
    {
        perror("[Server] bind failed. Error: ");
        return -1;
    }

    if (listen(this->listenfd, 10) < 0) {
        perror("[Server] listen failed. Error: ");
        return -1;
    }

    return 0;
}

int Server::close(void)
{
}


/*
Faire une boucle qui attend la connection des clients (condition arret ?)
=> Recevoir informations sur le personnage
=> Instancier le personnage et faire un Game:getInstance()->addPlayer(p)
=> Associer le player à un thread dans la map de clients
=> Lance le thread de reception de message par client

Comment envoyer les infos aux clients ?
 */
int Server::run(void)
{
    int client_fd;
    int avatar_kind;
    int read_size;
    NetworkTermPlayer* player;

    while (1) {
        player = NULL;

        if ((client_fd =
             accept(this->listenfd, (struct sockaddr*)NULL, NULL)) < 0)
        {
            perror("[Server] accept failed. Error: ");
            return -1;
        }

        if ((read_size =
             recv(client_fd, &avatar_kind, sizeof(avatar_kind), 0)) <= 0)
        {
            perror("[Server] didn't receive avatar kind. Error: ");
            return -1;
        }

        switch ((avatar_kind_t)client_fd) {
          case AVATAR_KIND_DEFAULT:
            //player = new NetworkTermPlayer
            break;
        }
    }
    //Start thread for accepting new connections
    for (int i = 0; i < 3; i++) {
        int new_client;
        if ((new_client =
             accept(this->listenfd, (struct sockaddr*)NULL, NULL)) < 0)
        {
            perror("[Server] accept failed. Error: ");
            return -1;
        }
        this->clients.push_back(new_client);
    }

    //Wait for events
    for (int i = 0; i < 3; i++) {
        char buf[100];
        snprintf(buf, sizeof(buf), "Bonjour %d !\n", i);
        write(clients[i], buf, strlen(buf));
    }

    for (int i = 0; i < 3; i++) {
        close(clients[i]);
    }

    return 0;
}
