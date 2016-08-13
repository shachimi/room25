#ifndef CELL_HH_
# define CELL_HH_

# include "room.hh"

class Cell {
public:
    Cell(int pos);
    ~Cell(void);

    void print(std::ostream& out);


    /* Getter and setters */
    int getPos(void) { return this->pos; };
    int getX(void) { return this->pos % 5; };
    int getY(void) { return this->pos / 5; };
    Room *getRoom(void) { return this->room; };
    void setRoom(Room *room);

    Cell *getLeft(void) { return this->left; };
    Cell *getRight(void) { return this->right; };
    Cell *getUp(void) { return this->up; };
    Cell *getDown(void) { return this->down; };
    void setLeft(Cell *cell) {  this->left = cell; };
    void setRight(Cell *cell) {  this->right = cell; };
    void setUp(Cell *cell) {  this->up = cell; };
    void setDown(Cell *cell) {  this->down = cell; };

private:
    int pos;
    Room *room;
    Cell *left;
    Cell *right;
    Cell *up;
    Cell *down;
};

#endif /* !CELL_HH_ */
