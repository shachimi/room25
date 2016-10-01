#ifndef MESSAGE_FACTORY_HH_
# define MESSAGE_FACTORY_HH_

# include "network/enum.hh"
# include "network/message.hh"
# include "network/push.hh"
# include "network/slide.hh"
# include "network/see.hh"
# include "network/move.hh"
# include "network/select-cell.hh"
# include "network/use-action.hh"

class MessageFactory {
public:
    static Message *getMessageFromNet(net_msg_t *msg);

private:
    static See *getSeeFromNet(net_msg_t *msg);
    static Move *getMoveFromNet(net_msg_t *msg);
    static Push *getPushFromNet(net_msg_t *msg);
    static Slide *getSlideFromNet(net_msg_t *msg);
    static SelectCell *getSelectCellFromNet(net_msg_t *msg);
    static UseAction *getUseActionFromNet(net_msg_t *msg);
};

#endif /* !MESSAGE_FACTORY_HH_ */