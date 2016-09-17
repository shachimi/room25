#ifndef SEE_MESSAGE_HH_
# define SEE_MESSAGE_HH_

# include "network/message.hh"

class See: public Message {
public:
    See(void);
    See(int id, int from, int to);
    ~See(void);

    virtual std::string to_str(void);
    // virtual net_msg_t to_net_msg(void);

public:
    int getId(void) { return this->id; };
    void setId(int id) { this->id = id; };
    int getFrom(void) { return this->from; };
    void setFrom(int from) { this->from = from; };
    int getTo(void) { return this->to; };
    void setTo(int to) { this->to = to; };

private:
    int id;
    int from;
    int to;
};

#endif /* !SEE_MESSAGE_HH_ */
