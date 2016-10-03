#ifndef MESSAGE_HH_
# define MESSAGE_HH_

# include <string>
# include "network/enum.hh"

/** Mother class to send/log event message of game. */
class Message {
public:
    virtual std::string to_str(void) = 0;
    virtual net_msg_t to_net_msg(void) = 0;

    int getId(void) { return this->id; };
    void setId(int id) { this->id = id; };

protected:
    int id;
};

#endif /* !MESSAGE_HH_ */
