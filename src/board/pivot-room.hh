#ifndef PIVOT_ROOM_HH_
# define PIVOT_ROOM_HH_

# include "room_effect.hh"

class PivotRoom : public RoomEffect {
public:
    PivotRoom(void);
    ~PivotRoom(void);
    virtual void prisoner_enter(Avatar *prisoner);
    virtual int validateDirection(int directions, action_t action);

private:
    int directions;
};

#endif /* !PIVOT_ROOM_HH_ */
