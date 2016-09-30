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

    int getId(void) { return this->id; };
    void setId(int id) { this->id = id; };
    bool getValue(void) { return this->value; };
    void setValue(bool value) { this->value = value; };

private:
    int id;
    bool value;
};

#endif /* !USE_ACTION_HH_ */
