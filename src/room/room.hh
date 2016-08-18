#ifndef ROOM_HH_
# define ROOM_HH_

# include <iostream>
# include <vector>

# include "player/avatar.hh"

class Cell;
class RoomEffect;

class Room {
public:
    Room(void);
    ~Room(void);

    void print(std::ostream& out);
    void print(std::ostream& out, int inner_line);


public:
    /* Mechanic */
    void addAvatar(Avatar *avatar, bool activate_effect);
    void removeAvatar(Avatar *avatar);

    /* {{{ Getter and setters */
    RoomEffect *getEffect(void) const { return this->effect; };
    void setEffect(RoomEffect *effect);
    std::vector<Avatar *> getAvatars(void) const { return this->avatars; };
    Cell *getCell(void) const { return this->cell; };
    void setCell(Cell *cell) { this->cell = cell; };
    bool isVisible(void) const { return this->visible; };
    void setVisible(bool visible) { this->visible = visible; };
    bool isAccessible(void) const { return this->accessible; };
    void setAccessible(bool accessible) { this->accessible = accessible; };
    /* }}} */

protected:
    void setAvatars(std::vector<Avatar *> avatars) { this->avatars = avatars; };

protected:
    std::vector<Avatar *> avatars;
    Cell *cell;
    RoomEffect *effect;
    bool visible;
    bool accessible;
};

# include "room/cell.hh"
# include "room/room_effect.hh"

#endif /* !ROOM_HH_ */
