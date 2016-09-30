#ifndef AVATAR_FACTORY_HH_
# define AVATAR_FACTORY_HH_

# include "player/avatar.hh"
# include "game/enum.hh"

class AvatarFactory {
public:
    static Avatar *getPrisoner(Player *p);

    static Avatar *getAvatar(avatar_kind_t avatar_kind, Player *p);

private: /* Should never be instanciated */
    AvatarFactory() {};
    ~AvatarFactory() {};
};

#endif /* !AVATAR_FACTORY_HH_ */
