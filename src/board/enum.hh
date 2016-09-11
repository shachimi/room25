#ifndef BOARD_ENUM_HH_
# define BOARD_ENUM_HH_

/* XXX: Do not change the value of the enum since it will be pack
 *      on disc for backward compatibility
 */
typedef enum {
    EFFECT_DEADLY   = 0,
    EFFECT_ACID     = 1,
    EFFECT_FLOODING = 2,
    EFFECT_TORTURE  = 3,
    EFFECT_ILLUSION = 4,

    EFFECT_FREEZE   = 5,
    EFFECT_PRISON   = 6,
    EFFECT_FOG      = 7,
    EFFECT_VORTEX   = 8,
    EFFECT_PIVOT    = 9,

    EFFECT_CENTER   = 10,
    EFFECT_EXIT     = 11,
    EFFECT_SAFE     = 12,
    EFFECT_GEAR     = 13,
    EFFECT_VISION   = 14,
    EFFECT_WARP     = 15,
    EFFECT_TUNNEL   = 16,
    EFFECT_count,
} effect_t;

#endif /* !BOARD_ENUM_HH_ */
