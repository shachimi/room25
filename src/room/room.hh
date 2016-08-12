#ifndef ROOM_HH_
# define ROOM_HH_

# include <iostream>
# include <vector>

# include "player/player.hh"

class Cell;
class RoomEffect;

class Room {
public:
    Room(void);
    ~Room(void);

    void print(std::ostream& out);


public:
    /* Mechanic */
    void addPlayer(Player *player, bool activate_effect);
    void removePlayer(Player *player);

    /* Getter and setters */
    RoomEffect *getEffect(void) { return this->effect; };
    void setEffect(RoomEffect *effect) { this->effect = effect; };
    std::vector<Player *> getPlayers(void) { return this->players; };
    void setPlayers(std::vector<Player *> players) { this->players = players; };
    Cell *getCell(void) { return this->cell; };
    void setCell(Cell *cell) { this->cell = cell; };
    bool isVisible(void) { return this->visible; };
    void setVisible(bool visible) { this->visible = visible; };

protected:
    std::vector<Player *> players;
    Cell *cell;
    RoomEffect *effect;
    bool visible;
};

# include "cell.hh"
# include "room_effect.hh"

#endif /* !ROOM_HH_ */
