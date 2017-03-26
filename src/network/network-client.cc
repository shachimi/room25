#include "network/network-client.hh"

NetworkClient::NetworkClient()
{
}

NetworkClient::~NetworkClient()
{
    if (getSock() >= 0) {
        close(getSock());
    }
}

int NetworkClient::connect(const int port)
{
    connect(port, NULL);
}

int NetworkClient::connect(const int port, const char *address)
{
    struct sockaddr_in serv_addr;

    // Connect to the server listening socket
    if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("[Network] Error creating socket: ");
        return -1;
    }
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, address, &serv_addr.sin_addr) <= 0) {
        perror("[Network] inet_pton error: ");
        return -1;
    }
    if (::connect(this->getSock(), (struct sockaddr *)&serv_addr,
                sizeof(serv_addr)) < 0)
    {
        perror("[Network] Couldn't connect to the server: ");
        return -1;
    }

    return 0;
}


/* {{{ Tests */
#ifdef ZTEST_ON
# include "check/z.h"
# include <thread>
# include <condition_variable>

static int cond_var_count;

static int z_get_port() {
    static int z_port = 3938;

    return ++z_port;
}

static void z_thread_notify(std::condition_variable &cond_var)
{
    cond_var_count = 1;
    cond_var.notify_all();
}

static void z_thread_wait(std::condition_variable &cond_var,
                          std::mutex &mutex)
{
    std::unique_lock<std::mutex> lock(mutex);
    cond_var.wait(lock, [](){return cond_var_count == 1;});
}

static int z_create_fake_server(const int port, int max_connections)
{
    struct sockaddr_in serv_addr;
    int server_sock;
    int option;

    if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("[Network] Couldn't create socket: ");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    if (bind(server_sock, (struct sockaddr*)&serv_addr,
             sizeof(serv_addr)) < 0)
    {
        perror("[Network] Couldn't bind socket: ");
        return -1;
    }

    if (listen(server_sock, max_connections) < 0) {
        perror("[Network] Couldn't listen on socket: ");
        return -1;
    }

    return server_sock;
}

static int z_server_accept(const int server_sock)
{
    return accept(server_sock, (struct sockaddr *)NULL, NULL);
}

static net_msg_t z_recv(int sock)
{
    int code;
    net_msg_t msg;

    if ((code = read(sock, &msg, sizeof(msg)) < 0)) {
        perror("[Z] failed to recv msg");
    }

    return msg;
}

static int z_send(const net_msg_t &msg, int sock)
{
    int code;

    if ((code = write(sock, &msg, sizeof(msg)) < 0)) {
        perror("[Z] failed to send msg");
    }

    return code;
}

Z_GROUP(network_client, "")
{
    Z_TEST(connection, "NetworkClient connects to the server") {
        NetworkClient *network = new NetworkClient();
        std::thread *server_thread;
        std::condition_variable cond_var;
        std::mutex mutex;
        const int port = z_get_port();

        cond_var_count = 0;
        server_thread = new std::thread([&port, &cond_var](){
            int server_sock;

            server_sock = z_create_fake_server(port, 1);
            z_thread_notify(cond_var);
            z_server_accept(server_sock);

            close(server_sock);
        });

        z_thread_wait(cond_var, mutex);
        Z_ASSERT(network->connect(port, "127.0.0.1") >= 0);

        server_thread->join();
        delete network;
    } Z_TEST_END;

    Z_TEST(send, "NetworkClient sends a message to the server") {
        NetworkClient *network = new NetworkClient();
        std::thread *server_thread;
        std::condition_variable cond_var;
        std::mutex mutex;
        const int port = z_get_port();
        net_msg_t msg;
        net_msg_t recv_msg;

        recv_msg.c = 'z';

        cond_var_count = 0;
        server_thread = new std::thread([&port, &cond_var, &recv_msg](){
            int server_sock;
            int client_sock;

            server_sock = z_create_fake_server(port, 1);
            z_thread_notify(cond_var);
            client_sock = z_server_accept(server_sock);
            recv_msg = z_recv(client_sock);

            close(server_sock);
        });

        z_thread_wait(cond_var, mutex);
        Z_ASSERT(network->connect(port, "127.0.0.1") >= 0);

        msg.type = NET_MSG_CHAR;
        msg.c = 'a';
        Z_ASSERT(network->send(msg) >= 0);

        server_thread->join();
        Z_ASSERT(recv_msg.type == NET_MSG_CHAR);
        Z_ASSERT(recv_msg.c == 'a');

        delete network;
    } Z_TEST_END;

    Z_TEST(recv, "NetworkClient sends a message to the server") {
        NetworkClient *network = new NetworkClient();
        std::thread *server_thread;
        std::condition_variable cond_var;
        std::mutex mutex;
        const int port = z_get_port();
        net_msg_t recv_msg;

        recv_msg.c = 'z';

        cond_var_count = 0;
        server_thread = new std::thread([&port, &cond_var, &recv_msg](){
            int server_sock;
            int client_sock;
            net_msg_t msg;

            server_sock = z_create_fake_server(port, 1);
            z_thread_notify(cond_var);
            client_sock = z_server_accept(server_sock);
            msg.type = NET_MSG_CHAR;
            msg.c = 'a';
            z_send(msg, client_sock);

            close(server_sock);
        });

        z_thread_wait(cond_var, mutex);
        Z_ASSERT(network->connect(port, "127.0.0.1") >= 0);

        recv_msg = network->recv();
        Z_ASSERT(recv_msg.type == NET_MSG_CHAR);
        Z_ASSERT(recv_msg.c == 'a');

        server_thread->join();
        delete network;
    } Z_TEST_END;
}
#endif
/* }}} */
