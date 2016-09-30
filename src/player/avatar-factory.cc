#include "player/avatar-factory.hh"
#include "player/prisonner.hh"

Avatar *AvatarFactory::getAvatar(avatar_kind_t avatar_kind, Player *p)
{
    if (avatar_kind == AVATAR_KIND_PRISONER) {
        return AvatarFactory::getPrisoner(p);
    }
    return NULL;
}

Avatar *AvatarFactory::getPrisoner(Player *p)
{
    return new Prisoner(p);
}
