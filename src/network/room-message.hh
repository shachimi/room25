#ifndef ROOM_MESSAGE_HH_
# define ROOM_MESSAGE_HH_

# include "game/enum.hh"
# include "board/enum.hh"
# include "network/message.hh"

class RoomMsg: public Message {
public:
    RoomMsg(void);
    RoomMsg(int id, int pos, effect_t effect);
    ~RoomMsg(void);

    virtual std::string to_str(void);
    virtual net_msg_t to_net_msg(void);

public:
    int getPos(void) { return this->pos; };
    void setPos(int pos) { this->pos = pos; };
    effect_t getEffect(void) { return this->effect; };
    void setEffect(effect_t effect) { this->effect = effect; };

private:
    int pos;
    effect_t effect;
};

#endif /* !ROOM_MESSAGE_HH_ */
