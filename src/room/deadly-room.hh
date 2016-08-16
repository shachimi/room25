#ifndef DEADLY_ROOM_HH_
# define DEADLY_ROOM_HH_

# include "room_effect.hh"

class DeadlyRoom : public RoomEffect {
public:
    DeadlyRoom(void);
    ~DeadlyRoom(void);
    virtual void prisoner_enter(Player * prisoner);
    virtual void turn_starts(void);
    virtual void prisoner_stay(Player * prisoner);
    virtual void turn_ends(void);



    /* Getter and setters */
    std::vector<Player *> getPrisoners(void) { return this->prisoners; };
    void setPrisoners(std::vector<Player *> prisoners) { this->prisoners = prisoners; };

private:
    std::vector<Player *> prisoners;
};

#endif /* !DEADLY_ROOM_HH_ */
