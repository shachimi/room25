#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#include "network/enum.hh"
#include "board/enum.hh"

int connfd;

int send_req_create_cell(int id, int x, int y, effect_t effect, int is_visible);
int send_req_update_cell(int id, int x, int y, effect_t effect, int is_visible);

int send_req_create_player(int id, int x, int y, avatar_kind_t avatar_kind);
int send_req_update_player(int id, int x, int y, avatar_kind_t avatar_kind);

int send_req_set_rules(int nb_turn);

int main(int argc, char *argv[])
{
    int listenfd = 0;
    struct sockaddr_in serv_addr;
    net_msg_t msg;
    int code;

    connfd = 0;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(&msg, '0', sizeof(msg));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(listenfd, 10);

    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
    printf("Client connected ! (%d)\n", connfd);


    //Send board
    code = send_req_create_cell(0, 0, 0, EFFECT_CENTER, 0);
    code = send_req_create_cell(1, 1, 0, EFFECT_CENTER, 0);
    code = send_req_create_cell(2, 2, 0, EFFECT_CENTER, 0);
    code = send_req_create_cell(3, 3, 0, EFFECT_CENTER, 0);
    code = send_req_create_cell(4, 4, 0, EFFECT_CENTER, 0);//
    code = send_req_create_cell(5, 0, 1, EFFECT_CENTER, 0);
    code = send_req_create_cell(6, 1, 1, EFFECT_CENTER, 0);
    code = send_req_create_cell(7, 2, 1, EFFECT_CENTER, 0);
    code = send_req_create_cell(8, 3, 1, EFFECT_CENTER, 0);
    code = send_req_create_cell(9, 4, 1, EFFECT_CENTER, 0);//
    code = send_req_create_cell(10, 0, 2, EFFECT_CENTER, 0);
    code = send_req_create_cell(11, 1, 2, EFFECT_CENTER, 0);
    code = send_req_create_cell(12, 2, 2, EFFECT_CENTER, 0);
    code = send_req_create_cell(13, 3, 2, EFFECT_CENTER, 0);
    code = send_req_create_cell(14, 4, 2, EFFECT_CENTER, 0);//
    code = send_req_create_cell(15, 0, 3, EFFECT_CENTER, 0);
    code = send_req_create_cell(16, 1, 3, EFFECT_CENTER, 0);
    code = send_req_create_cell(17, 2, 3, EFFECT_CENTER, 0);
    code = send_req_create_cell(18, 3, 3, EFFECT_CENTER, 0);
    code = send_req_create_cell(19, 4, 3, EFFECT_CENTER, 0);//
    code = send_req_create_cell(20, 0, 4, EFFECT_CENTER, 0);
    code = send_req_create_cell(21, 1, 4, EFFECT_CENTER, 0);
    code = send_req_create_cell(22, 2, 4, EFFECT_CENTER, 0);
    code = send_req_create_cell(23, 3, 4, EFFECT_CENTER, 0);
    code = send_req_create_cell(24, 4, 4, EFFECT_CENTER, 0);

    // Set center room visible
    code = send_req_update_cell(12, 2, 2, EFFECT_CENTER, 1);

    // Set rules
    code = send_req_set_rules(10);

    // Create players
    code = send_req_create_player(1, 2, 2, AVATAR_KIND_PRISONER);
    code = send_req_create_player(2, 2, 2, AVATAR_KIND_PRISONER);

    //temporary board print request
    code = send_req_update_player(0, 0, 0, AVATAR_KIND_DEFAULT);

    if (code = read(connfd, &msg, sizeof(msg)+1) < 0) {
        perror("\n[Server] error receiving message from client: ");
        return -1;
    } else if (code == 0) {
        printf("Server lost connection to the client\n");
        return 0;
    }

    close(connfd);
    sleep(1);
}

int send_req_create_cell(int id, int x, int y, effect_t effect, int is_visible)
{
    net_msg_t msg;
    int code;

    msg.req = REQ_CREATE_CELL;
    msg.cell.id = id;
    msg.cell.coords.x = x;
    msg.cell.coords.y = y;
    msg.cell.effect = effect;
    msg.cell.is_visible = is_visible;
    code = write(connfd, &msg, sizeof(msg));

    printf("Sent REQ_CREATE_CELLS to the client. (%d)\n", code);

    return code;
}

int send_req_update_cell(int id, int x, int y, effect_t effect, int is_visible)
{
    net_msg_t msg;
    int code;

    msg.req = REQ_UPDATE_CELL;
    msg.cell.id = id;
    msg.cell.coords.x = x;
    msg.cell.coords.y = y;
    msg.cell.effect = effect;
    msg.cell.is_visible = is_visible;
    code = write(connfd, &msg, sizeof(msg));

    printf("Sent REQ_UPDATE_CELLS to the client. (%d)\n", code);

    return code;
}

int send_req_create_player(int id, int x, int y, avatar_kind_t avatar_kind)
{
    net_msg_t msg;
    int code;

    msg.req = REQ_CREATE_PLAYER;
    msg.player.id = id;
    msg.player.coords.x = x;
    msg.player.coords.y = y;
    msg.player.avatar_kind = avatar_kind;
    code = write(connfd, &msg, sizeof(msg));

    printf("Sent REQ_CREATE_PLAYER to the client. (%d)\n", code);

    return code;
}

int send_req_update_player(int id, int x, int y, avatar_kind_t avatar_kind)
{
    net_msg_t msg;
    int code;

    msg.req = REQ_UPDATE_PLAYER;
    msg.player.id = id;
    msg.player.coords.x = x;
    msg.player.coords.y = y;
    msg.player.avatar_kind = avatar_kind;
    code = write(connfd, &msg, sizeof(msg));

    printf("Sent REQ_UPDATE_PLAYER to the client. (%d)\n", code);

    return code;
}

int send_req_set_rules(int nb_turn)
{
    net_msg_t msg;
    int code;

    msg.req = REQ_SET_RULES;
    msg.rules.nb_turn = nb_turn;
    code = write(connfd, &msg, sizeof(msg));

    printf("Sent REQ_SET_RULES to the client. (%d)\n", code);

    return code;
}
