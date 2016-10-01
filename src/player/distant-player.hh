#ifndef DISTANT_PLAYER_HH_
# define DISTANT_PLAYER_HH_

# include "player/player.hh"

# include <vector>
# include "utils/Log.hh"
# include "board/enum.hh"
# include "game/enum.hh"
# include "player/avatar.hh"
# include "board/cell.hh"

// Static singleton class
class DistantPlayer : public Player {
public:
    DistantPlayer(int id);
    ~DistantPlayer(void);

    virtual Scheduling *getScheduling(void);
    virtual bool useAction(void);
    virtual direction_t selectMove(int allowed_dir);
    virtual direction_t selectSlide(int allowed_dir);
    virtual direction_t selectSee(int allowed_dir);
    virtual direction_t selectPushDirection(int allowed_dir);
    virtual Cell* selectCell(std::vector<Cell *> allowed_cells);
    virtual Avatar *selectPushTarget(std::vector<Avatar *> players);

    virtual void seeRoom(const Room *room);

    virtual void inform(Message *msg) {};

    void setSock(int sock) { this->sock = sock; };
    int getSock(void) { return this->sock; };

protected:
    int sock;
};

#endif /* !DISTANT_PLAYER_HH_ */
