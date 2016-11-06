#ifndef SCHEDULING_MESSAGE_HH_
# define SCHEDULING_MESSAGE_HH_

# include "game/enum.hh"
# include "board/enum.hh"
# include "network/message.hh"

class SchedulingMsg: public Message {
public:
    SchedulingMsg(void);
    SchedulingMsg(int owner, action_t action_1, action_t action_2, int adrenaline);
    ~SchedulingMsg(void);

    virtual std::string to_str(void);
    virtual net_msg_t to_net_msg(void);

public:
    int getOwner(void) { return this->getId(); };
    void setOwner(int owner) { this->setId(owner); };
    action_t getAction1(void) { return this->action_1; };
    void setAction1(action_t action) { this->action_1 = action; };
    action_t getAction2(void) { return this->action_2; };
    void setAction2(action_t action) { this->action_2 = action; };
    int getAdrenaline(void) { return this->adrenaline; };
    void setAdrenaline(int adrenaline) { this->adrenaline = adrenaline; };

private:
    action_t action_1;
    action_t action_2;
    int adrenaline;
};

#endif /* !SCHEDULING_MESSAGE_HH_ */
