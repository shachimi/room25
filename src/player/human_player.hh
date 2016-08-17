#ifndef HUMAN_PLAYER_HH_
# define HUMAN_PLAYER_HH_

# include "player.hh"

class HumanPlayer : Player {
public:
    virtual Action *getAction(void);
    virtual direction_t selectMove(int allowed_dir);
    virtual direction_t selectSlide(int allowed_dir);
    virtual direction_t selectSee(int allowed_dir);
    virtual direction_t selectPushDirection(int allowed_dir);
    virtual Avatar *selectPushTarget(std::vector<Avatar *> players);


    virtual void seeRoom(const Room *room);
};


#endif /* !HUMAN_PLAYER_HH_ */
