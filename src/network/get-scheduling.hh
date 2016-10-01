#ifndef GET_SCHEDULING_MESSAGE_HH_
# define GET_SCHEDULING_MESSAGE_HH_

# include "board/enum.hh"
# include "network/message.hh"

class GetScheduling: public Message {
public:
    GetScheduling(void);
    GetScheduling(int id, int adrenaline, action_t action_1, action_t action_2);
    ~GetScheduling(void);

    virtual std::string to_str(void);
    virtual net_msg_t to_net_msg(void);

public:
    action_t getAction(int turn);
    void setAction(action_t action, int turn) {
        if (turn == 1) {
            this->action_1 = action;
        } else {
            this->action_2 = action;
        }
    };
    int getId(void) const { return this->id; };
    void setId(int id) { this->id = id; };
    bool getAdrenaline(void) const { return this->adrenaline; };
    void setAdrenaline(bool adrenaline) { this->adrenaline = adrenaline; };
    int getAction1(void) const { return this->action_1; };
    int getAction2(void) const { return this->action_2; };

private:
    int id;
    int adrenaline;
    action_t action_1;
    action_t action_2;
};

#endif /* !GET_SCHEDULING_MESSAGE_HH_ */
