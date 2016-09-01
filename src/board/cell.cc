#include "cell.hh"

Cell::Cell(int pos)
    : pos(pos),
      room(NULL),
      left(NULL),
      right(NULL),
      up(NULL),
      down(NULL)
{
}

Cell::~Cell(void)
{
}

void Cell::setRoom(Room *room)
{
    this->room = room;
    if (room) {
        room->setCell(this);
    }
}

void Cell::print(std::ostream& out)
{
    this->room->print(out);
}

void Cell::print(std::ostream& out, int inner_line)
{
    this->room->print(out, inner_line);
}
