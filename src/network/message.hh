#ifndef MESSAGE_HH_
# define MESSAGE_HH_

# include <string>

/** Mother class to send/log event message of game. */
class Message {
public:
    virtual std::string to_str(void) = 0;
    // virtual net_msg_t to_net_msg(void) = 0;
};

#endif /* !MESSAGE_HH_ */
