#ifndef TORTURE_ROOM_HH_
# define TORTURE_ROOM_HH_

# include "player/player.hh"

class TortureRoom : RoomEffect {
public:
    TortureRoom(void);
    ~TortureRoom(void);
    virtual void prisoner_enter(Player *prisoner);
    virtual void turn_starts(void);
    virtual void prisoner_stay(Player *prisoner);
    virtual void turn_ends(void);


    /* Getter and setters */
    std::vector<Player *> getPrisoners(void) { return this->prisoners; };
    void setPrisoners(std::vector<Player *> prisoners) { this->prisoners = prisoners; };

private:
    std::vector<Player *> prisoners;
};

#endif /* !TORTURE_ROOM_HH_ */
