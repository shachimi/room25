#ifndef ROBOT_HH_
# define ROBOT_HH_

# include "player/avatar.hh"


class Robot : public Avatar {
public:
    Robot(void);
    ~Robot(void);

    virtual void destroy(void);
};

#endif /* !ROBOT_HH_ */
