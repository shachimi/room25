#include "room_effect.hh"

RoomEffect::RoomEffect(void)
{
}

RoomEffect::RoomEffect(room_kind_t kind)
    : kind(kind)
{
}

RoomEffect::~RoomEffect(void)
{
}

void RoomEffect::print(std::ostream& out)
{
    switch (this->kind) {
      case ROOM_KIND_DANGER: {
          out << "D";
      } break;
      case ROOM_KIND_SAFE: {
          out << "S";
      } break;
      case ROOM_KIND_EXIT: {
          out << "E";
      } break;
      case ROOM_KIND_CENTER: {
          out << "C";
      } break;
      case ROOM_KIND_OBS: {
          out << "W";
      } break;
    }
}

