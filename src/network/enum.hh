#ifndef NETWORK_ENUM_HH_
# define NETWORK_ENUM_HH_

typedef struct net_msg_t net_msg_t;

typedef enum net_msg_type_t {
    NET_MSG_CHAR,
} net_msg_type_t;

struct net_msg_t {
    net_msg_type_t type;
    union {
        char c;
    };
};

#endif /* NETWORK_ENUM_HH_ */
