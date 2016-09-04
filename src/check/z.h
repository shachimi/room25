#ifndef Z_H_
# define Z_H_

# include <iostream>

typedef struct {
    std::string name;
    bool (*test_cb)(void);
} z_test_t;

# define  Z_ASSERT(expr)                                                    \
    if (!(expr)) {                                                          \
        std::cerr << "Test " << __func__ << ": " #expr " failed at line "   \
                  << __LINE__ << std::endl;                                 \
        return false;                                                       \
    }                                                                       \

#define Z_GROUPS(_name, _cb)  groups.push_back((z_test_t){       \
       .name = _name, .test_cb = _cb                             \
   })


#endif
