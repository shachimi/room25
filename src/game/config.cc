#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "config.hh"

Config::Config(void)
    : nb_players(0)
{
    for (int i = 0; i < EFFECT_count; i++) {
        this->rooms[i].nb = 0;
        this->rooms[i].effect = (effect_t)i;
    }
}

Config::~Config(void)
{
}

int Config::load_config(const char *filename)
{
    int n;
    int fd = open(filename, O_RDONLY);

    if (fd < 0) {
        perror("unable to load file");
        return -1;
    }
    read(fd, &this->nb_players, sizeof(int));
    read(fd, &n, sizeof(int));
    for (int i = 0; i < n; i++) {
        rooms_config_t rooms;

        read(fd, &rooms, sizeof(rooms_config_t));
        this->rooms[rooms.effect].nb = rooms.nb;
    }
    close(fd);
    return 0;
}

int Config::save_config(const char *filename)
{
    int n = 0;
    int fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY,
                  S_IRUSR | S_IWUSR | S_IRGRP);

    if (fd < 0) {
        perror("unable to save file");
        return -1;
    }
    write(fd, &this->nb_players, sizeof(int));

    for (int i = 0; i < EFFECT_count; i++) {
        if (this->rooms[i].nb > 0) {
            n++;
        }
    }
    write(fd, &n, sizeof(int));
    for (int i = 0; i < n; i++) {
        if (this->rooms[i].nb > 0) {
            write(fd, &this->rooms[i], sizeof(rooms_config_t));
        }
    }

    close(fd);
    return 0;
}

void Config::print(void) {
    printf("config:\nnb_player: %d\n", this->nb_players);
    for (int i = 0; i < EFFECT_count; i++) {
        if (this->rooms[i].nb > 0) {
            printf("rooms: (%d, %d)\n", this->rooms[i].nb,
                   this->rooms[i].effect);

        }
    }
}
