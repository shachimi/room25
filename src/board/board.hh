#ifndef BOARD_HH_
# define BOARD_HH_

# include <iostream>
# include <vector>

# include "game/enum.hh"
# include "board/cell.hh"
# include "board/tunnel-room.hh"
# include "player/player.hh"
# include "player/avatar.hh"

class Board {
public:
    Board(void);
    Board(std::vector<Room *> rooms);
    ~Board(void);

    void shuffle(void);

    void set_avatar_to_center(Avatar *avatar);

    /* Getter and setters */
    int getL(void) { return this->l; };
    Cell *getCell(int pos) { return this->cells[pos]; };
    Cell *getCell(int x, int y) { return this->cells[x + y * 5]; };
    Cell *getCellById(int id);
    std::vector<Cell *> getCells(void) { return this->cells; };
    Cell *getCenterCell(void) { return this->center; };
    std::vector<Cell *> getNoCenterCells(void);
    std::vector<RoomEffect *> getTunnelRoomEffects(void) { return this->tunnel_room_effects; };
    int getPos(int x, int y) { return (x + y * this->l); };

    void setCells(std::vector<Cell *> cells) { this->cells = cells; };
    void setCell(int x, int y, Cell *cell);

protected:
    void linkCell(int x, int y, Cell *cell);

public: /* game mechanics */
    void slide(int x, int y, direction_t direction);
    void slide(Player *owner, direction_t direction);
    void move(Player *owner, direction_t direction);
    void push(Player *owner, Avatar *target, direction_t direction);
    room_kind_t see(Player *owner, direction_t direction);

    void print(std::ostream& out) const;

protected:
    int l;
    std::vector<Cell *> cells;
    Cell *center; /* do not free */
    std::vector<RoomEffect *> tunnel_room_effects;
};

#endif /* !BOARD_HH_ */
