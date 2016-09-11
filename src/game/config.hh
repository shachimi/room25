#ifndef CONFIG_HH_
# define CONFIG_HH_

# include "board/enum.hh"

typedef struct {
    int      nb;
    effect_t effect;
} rooms_config_t;

typedef struct {
    /** Number of players to wait to start the game */
    int nb_players;
    /** Rule to use for the game */
    /* mode_t mode; */
    /** Configuration of the complex */
    struct {
        int n;
        rooms_config_t *rooms;
    };
} config_t;


class Config {
public:
    Config(void);
    ~Config(void);

    int load_config(const char *filename);
    int save_config(const char *filename);

    void print(void);

public:
    int getNbPlayers(void) { return this->nb_players; };
    void setNbPlayers(int nb_players) { this->nb_players = nb_players; };
    int getNbRooms(effect_t effect) { return this->rooms[effect].nb; };
    void setNbRooms(effect_t effect, int nb) { this->rooms[effect].nb = nb; };

private:
    int nb_players;
    rooms_config_t rooms[EFFECT_count];
};

#endif /* !CONFIG_HH_ */
