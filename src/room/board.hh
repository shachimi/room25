#ifndef BOARD_HH_
# define BOARD_HH_

# include <iostream>
# include <vector>

# include "game/enum.hh"
# include "room/cell.hh"

class Board {
public:
    Board(void);
    ~Board(void);

    void shuffle(void);

    /* Getter and setters */
    Cell *getCell(int pos) { return this->cells[pos]; };
    Cell *getCell(int x, int y) { return this->cells[x + y * 5]; };
    std::vector<Cell *> getCells(void) { return this->cells; };

public: /* game mechanics */
    void slide(int x, int y, direction_t direction);
    void slide(Player *owner, direction_t direction);
    void move(Player *owner, direction_t direction);

    void print(std::ostream& out);

protected:
    std::vector<Cell *> cells;
};

#endif /* !BOARD_HH_ */
