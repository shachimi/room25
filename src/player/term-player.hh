#ifndef TERM_PLAYER_HH_
# define TERM_PLAYER_HH_

# include "player.hh"
# include "utils/utils.hh"

class TermPlayer : Player {
public:
    TermPlayer(int id);
    ~TermPlayer(void);

    virtual Scheduling *getScheduling(void);
    virtual bool useAction(void);
    virtual direction_t selectMove(int allowed_dir);
    virtual direction_t selectSlide(int allowed_dir);
    virtual direction_t selectSee(int allowed_dir);
    virtual direction_t selectPushDirection(int allowed_dir);
    virtual Cell* selectCell(std::vector<Cell *> allowed_cells);
    virtual Avatar *selectPushTarget(std::vector<Avatar *> players);


    virtual room_kind_t seeRoom(const Room *room);
    virtual void roomSaw(Player *p, room_kind_t kind);
    virtual void inform(Message *msg) {};
};


#endif /* !TERM_PLAYER_HH_ */
