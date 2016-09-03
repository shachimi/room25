#include "board.hh"
#include <assert.h>
#include <time.h>
#include <stdlib.h>

/* {{{ Initialize */

Board::Board(void)
    : l(5),
      cells(std::vector<Cell *>())
{
    int   i = 0;
    Cell *cell;

    for (int y = 0; y < this->l; y++) {
        for (int x = 0; x < this->l; x++) {
            Cell *cell = new Cell(x + this->l * y);

            this->cells.push_back(cell);
            if (0 < x) {
                Cell *tmp = this->cells[x - 1 + y * this->l];

                tmp->setRight(cell);
                cell->setLeft(tmp);
            }
            if (0 < y) {
                Cell *tmp = this->cells[x + (y - 1) * this->l];

                tmp->setDown(cell);
                cell->setUp(tmp);
            }
        }
    }
    this->center = this->cells[this->l * this->l / 2];

    {
        Room *room = new Room();
        RoomEffect *effect = new RoomEffect();

        cell = this->getCell(this->l / 2, this->l / 2);
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

        if (i == this->l * this->l / 2) {
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
    this->shuffle();
}

Board::Board(std::vector<Room *> rooms)
    : l(5),
      cells(std::vector<Cell *>())
{
    int   i = 0;
    Cell *cell;

    for (int y = 0; y < this->l; y++) {
        for (int x = 0; x < this->l; x++) {
            Cell *cell = new Cell(x + this->l * y);

            this->cells.push_back(cell);
            if (0 < x) {
                Cell *tmp = this->cells[x - 1 + y * this->l];

                tmp->setRight(cell);
                cell->setLeft(tmp);
            }
            if (0 < y) {
                Cell *tmp = this->cells[x + (y - 1) * this->l];

                tmp->setDown(cell);
                cell->setUp(tmp);
            }
        }
    }
    this->center = this->cells[this->l * this->l / 2];
    {
        Room *room = new Room();
        RoomEffect *effect = new RoomEffect();

        effect->setKind(ROOM_KIND_CENTER);
        room->setEffect(effect);
        room->setVisible(true);
        rooms.push_back(room);
    }
    {
        Room *room = new Room();
        RoomEffect *effect = new RoomEffect();

        effect->setKind(ROOM_KIND_EXIT);
        room->setEffect(effect);
        rooms.push_back(room);
    }
    assert (rooms.size() == this->cells.size());

    for (int i = 0; i < this->l * this->l; i++) {
        this->cells[i]->setRoom(rooms[i]);
    }
    this->shuffle();
}

Board::~Board(void)
{
}

void Board::shuffle(void)
{
    Room *center;
    Room *exit;
    std::vector<Room *> rooms = std::vector<Room *>();

    for (int i = 0; i < this->cells.size(); i++) {
        Room *room = this->cells[i]->getRoom();

        if (room->getEffect()->getKind() == ROOM_KIND_CENTER) {
            center = room;
        } else
        if (room->getEffect()->getKind() == ROOM_KIND_EXIT) {
            exit = room;
        } else {
            rooms.push_back(room);
        }
        this->cells[i]->setRoom(NULL);
    }
    assert (rooms.size() == this->cells.size() - 2);

    srand(time(NULL));
    for (int i = 0; i < rooms.size() * 2; i++) {
        Room *tmp;
        int idx = rand() % rooms.size();

        tmp = rooms[idx];
        rooms[idx] = rooms[i % rooms.size()];
        rooms[i % rooms.size()] = tmp;
    }
    for (int i = 0; i < this->l / 2; i++) {
        for (int j = -i; j <= i; j++) {
            Cell *cell = this->cells[this->l / 2 + i * j + this->l * i];

            cell->setRoom(rooms.back());
            rooms.pop_back();
        }
    }
    this->cells[this->l * this->l / 2]->setRoom(center);
    for (int i = this->l / 2 + 1; i < this->l; i++) {
        for (int j = (i + 1) - this->l; j <= this->l - (i + 1); j++) {
            Cell *cell = this->cells[this->l / 2 + i * j + this->l * i];

            cell->setRoom(rooms.back());
            rooms.pop_back();
        }
    }
    rooms.push_back(exit);
    {
        Room *tmp;
        int idx = rand() % rooms.size();

        tmp = rooms[idx];
        rooms[idx] = rooms[rooms.size() - 1];
        rooms[rooms.size() - 1] = tmp;
    }
    for (int i = 0; i < this->l * this->l; i++) {
        if (!this->cells[i]->getRoom()) {
            this->cells[i]->setRoom(rooms.back());
            rooms.pop_back();
        }
    }
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

    switch (direction) {
      case DIRECTION_DOWN: {
          /* Get extremity */
          cur = get_line_beginning(this->cells[origin], DIRECTION_DOWN);
          room = cur->getRoom();
          /* Move room by going the awaiting way and putting the room inside */
          while (cur->getUp()) {
              cur->setRoom(cur->getUp()->getRoom());
              cur->markCell(DIRECTION_DOWN);
              cur = cur->getUp();
          }
          cur->setRoom(room);
          cur->markCell(DIRECTION_DOWN);
      } break;

      case DIRECTION_UP: {
          /* Get extremity */
          cur = get_line_beginning(this->cells[origin], DIRECTION_UP);
          room = cur->getRoom();
          /* Move room by going the awaiting way and putting the room inside */
          while (cur->getDown()) {
              cur->setRoom(cur->getDown()->getRoom());
              cur->markCell(DIRECTION_UP);
              cur = cur->getDown();
          }
          cur->setRoom(room);
          cur->markCell(DIRECTION_UP);
      } break;

      case DIRECTION_RIGHT: {
          /* Get extremity */
          cur = get_line_beginning(this->cells[origin], DIRECTION_RIGHT);
          room = cur->getRoom();
          /* Move room by going the awaiting way and putting the room inside */
          while (cur->getLeft()) {
              cur->setRoom(cur->getLeft()->getRoom());
              cur->markCell(DIRECTION_RIGHT);
              cur = cur->getLeft();
          }
          cur->setRoom(room);
          cur->markCell(DIRECTION_RIGHT);
      } break;

      case DIRECTION_LEFT: {
          /* Get extremity */
          cur = get_line_beginning(this->cells[origin], DIRECTION_LEFT);
          room = cur->getRoom();
          /* Move room by going the awaiting way and putting the room inside */
          while (cur->getRight()) {
              cur->setRoom(cur->getRight()->getRoom());
              cur->markCell(DIRECTION_LEFT);
              cur = cur->getRight();
          }
          cur->setRoom(room);
          cur->markCell(DIRECTION_LEFT);
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

void Board::set_avatar_to_center(Avatar *avatar)
{
    this->center->getRoom()->addAvatar(avatar, false);
}

/* }}} */

std::vector<Cell *> Board::getNoCenterCells(void)
{
    std::vector<Cell *> cells = this->getCells();
    std::vector<Cell *>::iterator it;

    for ( it = cells.begin(); it < cells.end(); it++) {
        if ( (*it)->getRoom()->getEffect()->getKind() == ROOM_KIND_CENTER ) {
            cells.erase(it);
        }
    }
    
    return cells;
}
