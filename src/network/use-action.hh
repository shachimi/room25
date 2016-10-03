#ifndef USE_ACTION_HH_
# define USE_ACTION_HH_

# include "network/message.hh"

class UseAction: public Message {
public:
    UseAction(void);
    UseAction(int id, bool value);
    ~UseAction(void);

    virtual std::string to_str(void);
    virtual net_msg_t to_net_msg(void);

    bool getValue(void) { return this->value; };
    void setValue(bool value) { this->value = value; };

private:
    bool value;
};

#endif /* !USE_ACTION_HH_ */
