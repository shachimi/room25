#ifndef BOARD_ENUM_HH_
# define BOARD_ENUM_HH_

# include <string>

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

    EFFECT_NONE = -1,
} effect_t;

# include <string.h>
# define STRCMP(_str, _ref)  strncmp(_str, _ref, sizeof(_ref))
static effect_t str_to_effect(const char *str) {
    if (STRCMP(str, "EFFECT_DEADLY") || STRCMP(str, "DEADLY")) {
        return EFFECT_DEADLY;
    }
    if (STRCMP(str, "EFFECT_ACID") || STRCMP(str, "ACID")) {
        return EFFECT_ACID;
    }
    if (STRCMP(str, "EFFECT_FLOODING") || STRCMP(str, "FLOODING")) {
        return EFFECT_FLOODING;
    }
    if (STRCMP(str, "EFFECT_TORTURE") || STRCMP(str, "TORTURE")) {
        return EFFECT_TORTURE;
    }
    if (STRCMP(str, "EFFECT_ILLUSION") || STRCMP(str, "ILLUSION")) {
        return EFFECT_ILLUSION;
    }
    if (STRCMP(str, "EFFECT_FREEZE") || STRCMP(str, "FREEZE")) {
        return EFFECT_FREEZE;
    }
    if (STRCMP(str, "EFFECT_PRISON") || STRCMP(str, "PRISON")) {
        return EFFECT_PRISON;
    }
    if (STRCMP(str, "EFFECT_FOG") || STRCMP(str, "FOG")) {
        return EFFECT_FOG;
    }
    if (STRCMP(str, "EFFECT_VORTEX") || STRCMP(str, "VORTEX")) {
        return EFFECT_VORTEX;
    }
    if (STRCMP(str, "EFFECT_PIVOT") || STRCMP(str, "PIVOT")) {
        return EFFECT_PIVOT;
    }
    if (STRCMP(str, "EFFECT_CENTER") || STRCMP(str, "CENTER")) {
        return EFFECT_CENTER;
    }
    if (STRCMP(str, "EFFECT_EXIT") || STRCMP(str, "EXIT")) {
        return EFFECT_EXIT;
    }
    if (STRCMP(str, "EFFECT_SAFE") || STRCMP(str, "SAFE")) {
        return EFFECT_SAFE;
    }
    if (STRCMP(str, "EFFECT_GEAR") || STRCMP(str, "GEAR")) {
        return EFFECT_GEAR;
    }
    if (STRCMP(str, "EFFECT_VISION") || STRCMP(str, "VISION")) {
        return EFFECT_VISION;
    }
    if (STRCMP(str, "EFFECT_WARP") || STRCMP(str, "WARP")) {
        return EFFECT_WARP;
    }
    if (STRCMP(str, "EFFECT_TUNNEL") || STRCMP(str, "TUNNEL")) {
        return EFFECT_TUNNEL;
    }
    return EFFECT_NONE;
}
# undef STRCMP

static std::string effect_to_str(effect_t effect) {
    switch (effect) {
      case EFFECT_DEADLY:
        return "DEADLY";
      case EFFECT_FLOODING:
        return "FLOODING";
      case EFFECT_ACID:
        return "ACID";
      case EFFECT_TORTURE:
        return "TORTURE";
      case EFFECT_ILLUSION:
        return "ILLUSION";
      case EFFECT_FREEZE:
        return "FREEZE";
      case EFFECT_FOG:
        return "FOG";
      case EFFECT_VORTEX:
        return "VORTEX";
      case EFFECT_PRISON:
        return "PRISON";
      case EFFECT_PIVOT:
        return "PIVOT";
      case EFFECT_CENTER:
        return "CENTER";
      case EFFECT_EXIT:
        return "EXIT";
      case EFFECT_SAFE:
        return "SAFE";
      case EFFECT_GEAR:
        return "GEAR";
      case EFFECT_VISION:
        return "VISION";
      case EFFECT_WARP:
        return "WARP";
      case EFFECT_TUNNEL:
        return "TUNNEL";
      default:
        return "";
    }
}

#endif /* !BOARD_ENUM_HH_ */
