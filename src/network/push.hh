#ifndef PUSH_MESSAGE_HH_
# define PUSH_MESSAGE_HH_

# include "board/enum.hh"
# include "network/message.hh"

class Push: public Message {
public:
    Push(void);
    Push(int id, int victim_id, int from, int to);
    ~Push(void);

    virtual std::string to_str(void);
    // virtual net_msg_t to_net_msg(void);

public:
    int getId(void) { return this->id; };
    void setId(int id) { this->id = id; };
    int getVictimId(void) { return this->victim_id; };
    void setVictimId(int victim_id) { this->victim_id = victim_id; };
    int getFrom(void) { return this->from; };
    void setFrom(int from) { this->from = from; };
    int getTo(void) { return this->to; };
    void setTo(int to) { this->to = to; };
    effect_t getToEffect(void) { return this->to_effect; };
    void setToEffect(effect_t to_effect) { this->to_effect = to_effect; };

private:
    int id;
    int victim_id;
    int from;
    int to;
    effect_t to_effect;
};

#endif /* !PUSH_MESSAGE_HH_ */
