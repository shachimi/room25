#include "board.hh"
#include <assert.h>


Board::Board(void)
    : cells(std::vector<Cell *>())
{
    int   i = 0;
    Cell *cell;

    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            Cell *cell = new Cell(x + 5 * y);

            this->cells.push_back(cell);
            if (0 < x) {
                Cell *tmp = this->cells[x - 1 + y * 5];

                tmp->setRight(cell);
                cell->setLeft(tmp);
            }
            if (0 < y) {
                Cell *tmp = this->cells[x + (y - 1) * 5];

                tmp->setDown(cell);
                cell->setUp(tmp);
            }
        }
    }

    {
        Player *p = new Player();
        Room *room = new Room();
        RoomEffect *effect = new RoomEffect();

        cell = this->getCell(2, 2);
        effect->setKind(ROOM_KIND_CENTER);
        room->setEffect(effect);
        room->setVisible(true);
        room->addPlayer(p, false);
        cell->setRoom(room);
    }
    {
        Room *room = new Room();
        RoomEffect *effect = new RoomEffect();

        effect->setKind(ROOM_KIND_EXIT);
        room->setEffect(effect);
        this->getCell(i)->setRoom(room);
    }
    for (i = 1; i < 11; i++) {
        Room *room = new Room();
        RoomEffect *effect = new RoomEffect();

        effect->setKind(ROOM_KIND_OBS);
        room->setEffect(effect);
        this->getCell(i)->setRoom(room);
    }
    for (; i < 17; i++) {
        Room *room = new Room();
        RoomEffect *effect = new RoomEffect();

        if (i == 12) {
            delete room;
            delete effect;
            continue;
        }

        effect->setKind(ROOM_KIND_DANGER);
        room->setEffect(effect);
        this->getCell(i)->setRoom(room);
    }
    for (; i < 25; i++) {
        Room *room = new Room();
        RoomEffect *effect = new RoomEffect();

        effect->setKind(ROOM_KIND_SAFE);
        room->setEffect(effect);
        this->getCell(i)->setRoom(room);
    }
}

Board::~Board(void)
{
}

void Board::shuffle(void)
{

}

void Board::print(std::ostream& out)
{
    out << " |";
    for (int x = 0; x < 5; x++) {
        out << x + 1 << "|";
    }
    out << std::endl;

    for (int x = 0; x < 5; x++) {
        out << x + 1 << "|";
        for (int y = 0; y < 5; y++) {
            this->cells[x * 5 + y]->print(out);
        }
        out << std::endl;
    }
}

/* {{{ Game mechanics */

static Cell *get_line_beginning(Cell *cell, direction_t dir)
{
    Cell *cur = cell;

    switch (dir) {
      case DIRECTION_N:
        while (cur->getUp()) {
            cur = cur->getUp();
        }
        break;

      case DIRECTION_E:
        while (cur->getRight()) {
            cur = cur->getRight();
        }
        break;

      case DIRECTION_S:
        while (cur->getDown()) {
            cur = cur->getDown();
        }
        break;

      case DIRECTION_O:
        while (cur->getLeft()) {
            cur = cur->getLeft();
        }
        break;
    }
    return cur;
}

void Board::slide(int x, int y, direction_t direction)
{
    int origin = x + y * 5;
    Cell *cur = NULL;
    Room *room = NULL;

    if (x < 0 || 4 < x) {
        assert (false);
        return;
    }
    if (y < 0 || 4 < y) {
        assert (false);
        return;
    }
    /* TODO look if the CENTER room is inside the line */
    if (x == 2 && (direction == DIRECTION_N || direction == DIRECTION_S)
    ||  y == 2 && (direction == DIRECTION_O || direction == DIRECTION_E))
    {
        std::cerr << "could not slide with the center" << std::endl;
        return;
    }
#if 0
    /* Column */
    if (origin + direction < 0 || 5 < origin + direction) {
        std::cerr << "attempting to move into a wrong direction" << std::endl;
        return;
    }

    /* Line */
    if (x + direction < 0 || 5 < x + direction) {
        std::cerr << "attempting to move into a wrong direction" << std::endl;
        return;
    }

#endif
    /* TODO: mark the direction of the column */
    switch (direction) {
      case DIRECTION_S: {
          cur = get_line_beginning(this->cells[origin], DIRECTION_N);
          room = cur->getRoom();
          while (cur->getDown()) {
              cur->setRoom(cur->getDown()->getRoom());
              cur = cur->getDown();
          }
          cur->setRoom(room);
      } break;
      case DIRECTION_N: {
          cur = get_line_beginning(this->cells[origin], DIRECTION_S);
          room = cur->getRoom();
          while (cur->getUp()) {

              cur->setRoom(cur->getUp()->getRoom());
              cur = cur->getUp();
          }
          cur->setRoom(room);
      } break;

      case DIRECTION_O: {
          cur = get_line_beginning(this->cells[origin], DIRECTION_E);
          room = cur->getRoom();
          while (cur->getLeft()) {
              cur->setRoom(cur->getLeft()->getRoom());
              cur = cur->getLeft();
          }
          cur->setRoom(room);
      } break;

      case DIRECTION_E: {
          cur = get_line_beginning(this->cells[origin], DIRECTION_O);
          room = cur->getRoom();
          while (cur->getRight()) {
              cur->setRoom(cur->getRight()->getRoom());
              cur = cur->getRight();
          }
          cur->setRoom(room);
      } break;
    }
}

void Board::move(Player *owner, direction_t direction)
{
    Cell *origin = owner->getRoom()->getCell();
    int x = origin->getPos() % 5;
    int y = origin->getPos() / 5;

    /* Column */
    std::cerr << origin->getPos() << "  |  " << direction << std::endl;
    if (origin->getPos() + direction < 0 || 24 < origin->getPos() + direction)
    {
        std::cerr << "attempting to move into a wrong direction NS" << std::endl;
        return;
    }
    /* Line */
    if (x + direction % 5 < 0 || 4 < x + direction % 5) {
        std::cerr << "attempting to move into a wrong direction OE" << std::endl;
        return;
    }

    /* TODO: is the room locked (flooding) */
    origin->getRoom()->removePlayer(owner);
    switch (direction) {
      case DIRECTION_N:
        origin->getUp()->getRoom()->addPlayer(owner, true);
        break;
      case DIRECTION_S:
        origin->getDown()->getRoom()->addPlayer(owner, true);
        break;
      case DIRECTION_E:
        origin->getRight()->getRoom()->addPlayer(owner, true);
        break;
      case DIRECTION_O:
        origin->getLeft()->getRoom()->addPlayer(owner, true);
        break;
    }
}

/* }}} */

