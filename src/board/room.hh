#ifndef ROOM_HH_
# define ROOM_HH_

# include <iostream>
# include <vector>

# include "game/enum.hh"
# include "player/avatar.hh"

class Cell;
class RoomEffect;
class Scheduling;

class Room {
public:
    Room(void);
    ~Room(void);

    void print(std::ostream& out);
    void print(std::ostream& out, int inner_line);

    bool validateSchedule(Scheduling *scheduling);

public:
    /* Mechanic */
    void addAvatar(Avatar *avatar, bool activate_effect);
    void removeAvatar(Avatar *avatar);

    /* {{{ Getter and setters */
    room_kind_t getRoomKind(void) const;
    RoomEffect *getEffect(void) const { return this->effect; };
    void setEffect(RoomEffect *effect);
    std::vector<Avatar *> getAvatars(void) const { return this->avatars; };
    Cell *getCell(void) const { return this->cell; };
    void setCell(Cell *cell) { this->cell = cell; };
    bool isVisible(void) const { return this->visible; };
    void setVisible(bool visible) { this->visible = visible; };
    bool isAccessible(void) const { return this->accessible; };
    void setAccessible(bool accessible) { this->accessible = accessible; };
    int getAvatarsNb(void) { return this->avatars.size(); };
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

# include "game/scheduling.hh"
# include "board/cell.hh"
# include "board/room_effect.hh"


#endif /* !ROOM_HH_ */
