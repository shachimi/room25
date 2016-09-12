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

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;
    net_msg_t msg;
    int code;

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

    msg.req = REQ_CREATE_CELL;
    msg.cell.id = 0;
    msg.cell.coords.x = 1;
    msg.cell.coords.y = 1;
    msg.cell.effect = EFFECT_CENTER;
    msg.cell.is_visible = 0;
    code = write(connfd, &msg, sizeof(msg));
    printf("Sent request 1 to the client. (%d)\n", code);

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
