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
    std::vector<Cell *> getCells(void) { return this->cells; };
    std::vector<Cell *> getNoCenterCells(void);
    std::vector<RoomEffect *> getTunnelRoomEffects(void) { return this->tunnel_room_effects; };

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
