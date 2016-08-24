#include "board.hh"
#include <assert.h>

/* {{{ Initialize */

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
        Room *room = new Room();
        RoomEffect *effect = new RoomEffect();

        cell = this->getCell(2, 2);
        effect->setKind(ROOM_KIND_CENTER);
        room->setEffect(effect);
        room->setVisible(true);
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

void Board::print(std::ostream& out) const
{
    out << "   |";
    for (int x = 0; x < 5; x++) {
        out << " " << x + 1 << " |";
    }
    out << std::endl;
    out << "---+---+---+---+---+---+" << std::endl;

    for (int x = 0; x < 5; x++) {
        out << "   |";
        for (int y = 0; y < 5; y++) {
            this->cells[x * 5 + y]->print(out, 1);
            out << "|";
        }
        out << std::endl << " " << x + 1 << " |";
        for (int y = 0; y < 5; y++) {
            this->cells[x * 5 + y]->print(out, 2);
            out << "|";
        }
        out << std::endl << "   |";
        for (int y = 0; y < 5; y++) {
            this->cells[x * 5 + y]->print(out, 3);
            out << "|";
        }
        out << std::endl;
        out << "---+---+---+---+---+---+" << std::endl;
    }
}

/* }}} */
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

void Board::slide(Player *player, direction_t direction)
{
    Cell *cell = player->getAvatar()->getRoom()->getCell();

    return this->slide(cell->getX(), cell->getY(), direction);
}

void Board::slide(int x, int y, direction_t direction)
{
    int origin = x + y * 5;
    Cell *cur = NULL;
    Cell *begin = NULL;
    Room *room = NULL;

    if (x < 0 || 4 < x) {
        assert (false);
        return;
    }
    if (y < 0 || 4 < y) {
        assert (false);
        return;
    }

    if (x == 2 && (direction == DIRECTION_N || direction == DIRECTION_S)
    ||  y == 2 && (direction == DIRECTION_O || direction == DIRECTION_E))
    {
        std::cerr << "could not slide with the center" << std::endl;
        return;
    }

    /* TODO: mark the direction of the column/line */
    switch (direction) {
      case DIRECTION_DOWN: {
          /* Get extremity */
          cur = get_line_beginning(this->cells[origin], DIRECTION_DOWN);
          room = cur->getRoom();
          /* Move room by going the awaiting way and putting the room inside */
          while (cur->getUp()) {
              cur->setRoom(cur->getUp()->getRoom());
              cur = cur->getUp();
          }
          cur->setRoom(room);
      } break;
      case DIRECTION_UP: {
          /* Get extremity */
          cur = get_line_beginning(this->cells[origin], DIRECTION_UP);
          room = cur->getRoom();
          /* Move room by going the awaiting way and putting the room inside */
          while (cur->getDown()) {
              cur->setRoom(cur->getDown()->getRoom());
              cur = cur->getDown();
          }
          cur->setRoom(room);
      } break;

      case DIRECTION_RIGHT: {
          /* Get extremity */
          cur = get_line_beginning(this->cells[origin], DIRECTION_RIGHT);
          room = cur->getRoom();
          /* Move room by going the awaiting way and putting the room inside */
          while (cur->getLeft()) {
              cur->setRoom(cur->getLeft()->getRoom());
              cur = cur->getLeft();
          }
          cur->setRoom(room);
      } break;

      case DIRECTION_LEFT: {
          /* Get extremity */
          cur = get_line_beginning(this->cells[origin], DIRECTION_LEFT);
          room = cur->getRoom();
          /* Move room by going the awaiting way and putting the room inside */
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
    Cell *origin = owner->getAvatar()->getRoom()->getCell();
    int x = origin->getPos() % 5;
    int y = origin->getPos() / 5;

    /* Column */
    if ((y == 0 && direction == DIRECTION_N)
    ||  (y == 4 && direction == DIRECTION_S))
    {
        std::cerr << "attempting to move into a wrong direction NS" << std::endl;
        return;
    }
    /* Line */
    if ((x == 0 && direction == DIRECTION_O)
    ||  (x == 4 && direction == DIRECTION_E))
    {
        std::cerr << "attempting to move into a wrong direction OE" << std::endl;
        return;
    }

    /* TODO: is the room locked (flooding) */
    origin->getRoom()->removeAvatar(owner->getAvatar());
    switch (direction) {
      case DIRECTION_UP:
        origin->getUp()->getRoom()->addAvatar(owner->getAvatar(), true);
        break;
      case DIRECTION_DOWN:
        origin->getDown()->getRoom()->addAvatar(owner->getAvatar(), true);
        break;
      case DIRECTION_RIGHT:
        origin->getRight()->getRoom()->addAvatar(owner->getAvatar(), true);
        break;
      case DIRECTION_LEFT:
        origin->getLeft()->getRoom()->addAvatar(owner->getAvatar(), true);
        break;
    }
}

void Board::push(Player *owner, Avatar *target, direction_t direction)
{
    Cell *origin = owner->getAvatar()->getRoom()->getCell();
    int x = origin->getPos() % 5;
    int y = origin->getPos() / 5;

    /* Column */
    if ((y == 0 && direction == DIRECTION_N)
    ||  (y == 4 && direction == DIRECTION_S))
    {
        std::cerr << "attempting to push into a wrong direction NS" << std::endl;
        return;
    }
    /* Line */
    if ((x == 0 && direction == DIRECTION_O)
    ||  (x == 4 && direction == DIRECTION_E))
    {
        std::cerr << "attempting to push into a wrong direction OE" << std::endl;
        return;
    }

    if (x == 2 && y == 2) {
        std::cerr << "you cannot push from the center room" << std::endl;
        return;
    }

    /* TODO: is the room locked (flooding) */
    origin->getRoom()->removeAvatar(target);
    switch (direction) {
      case DIRECTION_UP:
        origin->getUp()->getRoom()->addAvatar(target, true);
        break;
      case DIRECTION_DOWN:
        origin->getDown()->getRoom()->addAvatar(target, true);
        break;
      case DIRECTION_RIGHT:
        origin->getRight()->getRoom()->addAvatar(target, true);
        break;
      case DIRECTION_LEFT:
        origin->getLeft()->getRoom()->addAvatar(target, true);
        break;
    }
}

void Board::see(Player *owner, direction_t direction)
{
    Cell *origin = owner->getAvatar()->getRoom()->getCell();
    int x = origin->getPos() % 5;
    int y = origin->getPos() / 5;

    /* Column */
    if ((y == 0 && direction == DIRECTION_N)
    ||  (y == 4 && direction == DIRECTION_S))
    {
        std::cerr << "attempting to see into a wrong direction NS" << std::endl;
        return;
    }
    /* Line */
    if ((x == 0 && direction == DIRECTION_O)
    ||  (x == 4 && direction == DIRECTION_E))
    {
        std::cerr << "attempting to see into a wrong direction OE" << std::endl;
        return;
    }

    switch (direction) {
      case DIRECTION_UP:
        assert (!origin->getUp()->getRoom()->isVisible());
        owner->seeRoom(origin->getUp()->getRoom());
        break;
      case DIRECTION_DOWN:
        assert (!origin->getDown()->getRoom()->isVisible());
        owner->seeRoom(origin->getDown()->getRoom());
        break;
      case DIRECTION_RIGHT:
        assert (!origin->getRight()->getRoom()->isVisible());
        owner->seeRoom(origin->getRight()->getRoom());
        break;
      case DIRECTION_LEFT:
        assert (!origin->getLeft()->getRoom()->isVisible());
        owner->seeRoom(origin->getLeft()->getRoom());
        break;
    }
}

/* }}} */

