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
    int value;
} net_use_action_t;

typedef struct {
    int id;
    net_coords_t coords;
    effect_t effect;
    int is_visible;
} net_cell_t;

typedef struct {
    int id;
    int pos;
    avatar_kind_t avatar_kind;
} net_player_t;

typedef struct {
    int owner;
    action_t action_1;
    action_t action_2;
    int adrenaline;
} net_scheduling_t;

/* {{{ Action */

typedef struct {
    action_t action;
    int player_source_id;
    int player_target_id;
    direction_t direction;
} net_action_t;

typedef struct {
    int id;
    int from;
    int to;
    effect_t to_effect;
} net_move_t;

typedef struct {
    int id;
    int victim_id;
    int from;
    int to;
    effect_t to_effect;
} net_push_t;

typedef struct {
    int id;
    int from;
    int to;
} net_see_t;

typedef struct {
    int id;
    int from;
    direction_t dir;
} net_slide_t;

typedef struct {
    int id;
    int pos;
    effect_t effect;
} net_select_cell_t;

typedef struct {
    int id;
    int pos;
    effect_t effect;
} net_room_t;

/* }}} */

typedef struct {
    int nb_turn;
} net_rules_t;

typedef enum {
    // Game init
    REQ_PLAYER,
    REQ_ROOM,
    REQ_RULES,

    // Game loop
    REQ_SCHED,
    REQ_MOVE,
    REQ_PUSH,
    REQ_SEE,
    REQ_SLIDE,
    REQ_SELECT_CELL,
    REQ_USE_ACTION,

/* {{{ Action */
    REQ_ERROR_READ,
    REQ_ERROR_DISCONNECT,
    REQ_NONE,

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
/* }}} */
} net_req_t;

typedef struct {
    net_req_t req;
    union {
        net_cell_t cell;
        net_player_t player;
        net_scheduling_t scheduling;
        net_action_t action;
        net_rules_t rules;
        net_move_t move;
        net_push_t push;
        net_see_t see;
        net_slide_t slide;
        net_select_cell_t select_cell;
        net_use_action_t use_action;
        net_room_t room;
    };
} net_msg_t;

#endif /* !NETWORK_ENUM_HH_ */
