#ifndef TORTURE_ROOM_HH_
# define TORTURE_ROOM_HH_

# include "player/player.hh"

class TortureRoom : public RoomEffect {
public:
    TortureRoom(void);
    ~TortureRoom(void);
    virtual void prisoner_enter(Avatar *prisoner);
    virtual void turn_starts(void);
    virtual void prisoner_stay(Avatar *prisoner);
    virtual void turn_ends(void);


    /* Getter and setters */
    std::vector<Player *> getPrisoners(void) { return this->prisoners; };
    void setPrisoners(std::vector<Player *> prisoners) { this->prisoners = prisoners; };

private:
    std::vector<Player *> prisoners;
};

#endif /* !TORTURE_ROOM_HH_ */
