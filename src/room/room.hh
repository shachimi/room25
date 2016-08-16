#ifndef ROOM_HH_
# define ROOM_HH_

# include <iostream>
# include <vector>

# include "player/player.hh"
# include "room/room_effect.hh"

class Cell;

class Room {
public:
    Room(void);
    ~Room(void);

    void print(std::ostream& out);


public:
    /* Mechanic */
    void addPlayer(Player *player, bool activate_effect);
    void removePlayer(Player *player);

    /* {{{ Getter and setters */
    RoomEffect *getEffect(void) const { return this->effect; };
    void setEffect(RoomEffect *effect);
    std::vector<Player *> getPlayers(void) const { return this->players; };
    void setPlayers(std::vector<Player *> players) { this->players = players; };
    Cell *getCell(void) const { return this->cell; };
    void setCell(Cell *cell) { this->cell = cell; };
    bool isVisible(void) const { return this->visible; };
    void setVisible(bool visible) { this->visible = visible; };
    bool isAccessible(void) const { return this->accessible; };
    void setAccessible(bool accessible) { this->accessible = accessible; };
    /* }}} */

protected:
    std::vector<Player *> players;
    Cell *cell;
    RoomEffect *effect;
    bool visible;
    bool accessible;
};

# include "cell.hh"

#endif /* !ROOM_HH_ */
