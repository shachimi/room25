#include "utils/Log.hh"
#include "board/room-factory.hh"
#include "game/game.hh"
#include "game/standard-rule.hh"


StandardRule::StandardRule(void)
{
}

StandardRule::~StandardRule(void)
{
}

Board *StandardRule::init_board(std::vector<Room *> rooms)
{
    return new Board(rooms);
}

Board *StandardRule::init_board(void)
{
    std::vector<Room *> rooms = std::vector<Room *>();

    /* 4 deadly room */
    rooms.push_back(RoomFactory::getDeadlyRoom());
    rooms.push_back(RoomFactory::getDeadlyRoom());
    rooms.push_back(RoomFactory::getDeadlyRoom());
    rooms.push_back(RoomFactory::getDeadlyRoom());

    /* 9 safe room */
    rooms.push_back(RoomFactory::getSafeRoom());
    rooms.push_back(RoomFactory::getSafeRoom());
    rooms.push_back(RoomFactory::getSafeRoom());
    rooms.push_back(RoomFactory::getSafeRoom());
    rooms.push_back(RoomFactory::getSafeRoom());
    rooms.push_back(RoomFactory::getSafeRoom());
    rooms.push_back(RoomFactory::getSafeRoom());
    rooms.push_back(RoomFactory::getSafeRoom());
    rooms.push_back(RoomFactory::getSafeRoom());

    /* 5 flooding room */
    rooms.push_back(RoomFactory::getFloodingRoom());
    rooms.push_back(RoomFactory::getFloodingRoom());
    rooms.push_back(RoomFactory::getFloodingRoom());
    rooms.push_back(RoomFactory::getFloodingRoom());
    rooms.push_back(RoomFactory::getFloodingRoom());

    /* 3 acid room */
    rooms.push_back(RoomFactory::getAcidRoom());
    rooms.push_back(RoomFactory::getAcidRoom());
    rooms.push_back(RoomFactory::getAcidRoom());

    /* 2 torture room */
    rooms.push_back(RoomFactory::getTortureRoom());
    rooms.push_back(RoomFactory::getTortureRoom());

    return new Board(rooms);
}

bool StandardRule::manage_game(void)
{
    int turn;
    Game *game = Game::getInstance();

    try {
        for (turn = 1; turn <= this->turn; turn++) {
            Log::print() << "Turn" << turn << std::endl
                         << *game->getBoard() << std::endl;

            game->play_turn();
            game->rotatePlayer();
        }
    } catch (const char *message) {
        Log::print() << message << std::endl << *game->getBoard();
        return false;
    }
    return true;
}

bool StandardRule::destroyPrisoner(Prisoner *prisoner)
{
    return true;
}

