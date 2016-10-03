#ifndef PLAYER_MESSAGE_HH_
# define PLAYER_MESSAGE_HH_

# include "board/enum.hh"
# include "network/message.hh"

class PlayerMsg: public Message {
public:
    PlayerMsg(void);
    PlayerMsg(int id, int pos, avatar_kind_t avatar_kind);
    ~PlayerMsg(void);

    virtual std::string to_str(void);
    virtual net_msg_t to_net_msg(void);

public:
    int getPos(void) { return this->pos; };
    void setPos(int pos) { this->pos = pos; };
    avatar_kind_t getAvatarKind(void) { return this->to_effect; };
    void setAvatarKind(avatar_kind_t avatar_kind) { this->avatar_kind = avatar_kind; };

private:
    int pos;
    avatar_kind_t avatar_kind;
};

#endif /* !PLAYER_MESSAGE_HH_ */
