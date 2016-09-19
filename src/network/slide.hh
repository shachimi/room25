#ifndef SLIDE_MESSAGE_HH_
# define SLIDE_MESSAGE_HH_

# include "game/enum.hh"
# include "network/message.hh"

class Slide: public Message {
public:
    Slide(void);
    Slide(int id, int from, direction_t dir);
    ~Slide(void);

    virtual std::string to_str(void);
    virtual net_msg_t to_net_msg(void);

public:
    int getId(void) { return this->id; };
    void setId(int id) { this->id = id; };
    int getFrom(void) { return this->from; };
    void setFrom(int from) { this->from = from; };
    direction_t getDir(void) { return this->dir; };
    void setDir(direction_t dir) { this->dir = dir; };

private:
    int id;
    int from;
    direction_t dir;
};

#endif /* !SLIDE_MESSAGE_HH_ */
