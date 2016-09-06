#ifndef Z_H_
# define Z_H_

# include <iostream>
# include <vector>

typedef struct {
    std::string name;
    bool (*test_cb)(void);
} z_test_t;

extern std::vector<z_test_t> groups;

# define  Z_ASSERT(expr)                                                     \
    if (!(expr)) {                                                           \
        std::cerr << "Test " << __func__ << ": " #expr " failed at line "    \
                  << __LINE__ << std::endl;                                  \
        return false;                                                        \
    }

# define Z_TEST(_name, _cb)  groups.push_back((z_test_t){                    \
        .name = _name, .test_cb = _cb                                        \
   })

# define Z_GROUP(_name, _desc)                                               \
    static void init_##_name(std::string desc=_desc)

#endif
