#ifndef SELECT_CELL_MESSAGE_HH_
# define SELECT_CELL_MESSAGE_HH_

# include "board/enum.hh"
# include "network/message.hh"

class SelectCell: public Message {
public:
    SelectCell(void);
    SelectCell(int id, int pos, effect_t effect);
    ~SelectCell(void);

    virtual std::string to_str(void);
    virtual net_msg_t to_net_msg(void);

public:
    int getId(void) { return this->id; };
    void setId(int id) { this->id = id; };
    int getPos(void) { return this->pos; };
    void setPos(int pos) { this->pos = pos; };
    effect_t getEffect(void) { return this->effect; };
    void setEffect(effect_t effect) { this->effect = effect; };

private:
    int id;
    int pos;
    effect_t effect;
};

#endif /* !SELECT_CELL_MESSAGE_HH_ */
