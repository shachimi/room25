#ifndef CELL_HH_
# define CELL_HH_

# include "game/enum.hh"
# include "room.hh"

class Cell {
public:
    Cell(int pos);
    ~Cell(void);

    void print(std::ostream& out);
    void print(std::ostream& out, int inner_line);

    /* Getter and setters */
    int getPos(void) { return this->pos; };
    int getX(void) { return this->pos % 5; };
    int getY(void) { return this->pos / 5; };
    Room *getRoom(void) { return this->room; };
    void setRoom(Room *room);

    void markCell(direction_t dir) { this->slide_dirs |= dir; };
    int getSlideDirs(void) { return this->slide_dirs; };
    void setSlideDirs(int dirs) { this->slide_dirs = dirs; };

    Cell *getLeft(void) { return this->left; };
    Cell *getRight(void) { return this->right; };
    Cell *getUp(void) { return this->up; };
    Cell *getDown(void) { return this->down; };
    void setLeft(Cell *cell) {  this->left = cell; };
    void setRight(Cell *cell) {  this->right = cell; };
    void setUp(Cell *cell) {  this->up = cell; };
    void setDown(Cell *cell) {  this->down = cell; };

    void print(void) { 

private:
    int pos;
    int slide_dirs;
    Room *room;
    Cell *left;
    Cell *right;
    Cell *up;
    Cell *down;
};

#endif /* !CELL_HH_ */
