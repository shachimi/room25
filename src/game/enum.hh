#ifndef GAME_ENUM_HH_
# define GAME_ENUM_HH_

typedef enum {
    ACTION_NONE  = 0,
    ACTION_MOVE  = 1 << 0,
    ACTION_PUSH  = 1 << 1,
    ACTION_SLIDE = 1 << 2,
    ACTION_SEE   = 1 << 3,
    ACTION_SPEC  = 1 << 4,
    ACTION_ALL   = 0x1f,
} action_t;

typedef enum {
    DIRECTION_NONE = 0,
    DIRECTION_N = 1 << 0,
    DIRECTION_S = 1 << 1,
    DIRECTION_E = 1 << 2,
    DIRECTION_O = 1 << 3,
} direction_t;
#define DIRECTION_UP     DIRECTION_N
#define DIRECTION_DOWN   DIRECTION_S
#define DIRECTION_LEFT   DIRECTION_O
#define DIRECTION_RIGHT  DIRECTION_E

typedef enum {
    ROOM_KIND_CENTER,
    ROOM_KIND_EXIT,
    ROOM_KIND_SAFE,
    ROOM_KIND_OBS,
    ROOM_KIND_DANGER,
} room_kind_t;

#endif /* !GAME_ENUM_HH_ */
