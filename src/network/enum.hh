#ifndef NETWORK_ENUM_HH_
# define NETWORK_ENUM_HH_

# include "board/enum.hh"
# include "game/enum.hh"

typedef struct {
    int x;
    int y;
} net_coords_t;

typedef struct {
    int id;
    net_coords_t coords;
    effect_t effect;
    int is_visible;
} net_cell_t;

typedef struct {
    int id;
    net_coords_t coords;
    avatar_kind_t avatar_kind;
} net_player_t;

typedef struct {
    int player_id;
    action_t action_1;
    action_t action_2;
    int adrenaline;
} net_scheduling_t;

typedef struct {
    action_t action;
    int player_source_id;
    int player_target_id;
    direction_t direction;
} net_action_t;

typedef struct {
    int nb_turn;
} net_rules_t;

typedef enum {
    REQ_CREATE_CELL,
    REQ_UPDATE_CELL,
    REQ_CREATE_PLAYER,
    REQ_GET_PLAYER,
    REQ_UPDATE_PLAYER,
    REQ_GET_SCHEDULING,
    REQ_SET_SCHEDULING,
    REQ_GET_ACTION,
    REQ_SET_ACTION,
    REQ_FWD_ACTION,
    REQ_GET_EFFECT_ACTION,
    REQ_SET_EFFECT_ACTION,
    REQ_FWD_EFFECT_ACTION,
    REQ_SET_RULES,
} net_req_t;

typedef struct {
    net_req_t req;
    union {
        net_cell_t cell;
        net_player_t player;
        net_scheduling_t scheduling;
        net_action_t action;
        net_rules_t rules;
    };
} net_msg_t;

#endif /* !NETWORK_ENUM_HH_ */
