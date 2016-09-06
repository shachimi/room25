#ifndef Z_H_
# define Z_H_

# include <iostream>
# include <vector>
# include <map>

typedef struct {
    std::string name;
    bool (*test_cb)(void);
} z_test_t;

typedef std::vector<z_test_t> Group;
typedef std::map<std::string, Group> GroupMap;
extern GroupMap groups;

# define  Z_ASSERT(expr)                                                     \
    if (!(expr)) {                                                           \
        std::cerr << "Test " << __func__ << ": " #expr " failed at line "    \
                  << __LINE__ << std::endl;                                  \
        return false;                                                        \
    }

#define Z_TEST_NAME(_group, _cb) z_##_group##_##_cb

# define Z_TEST(_group, _cb)                                                 \
    static bool Z_TEST_NAME(_group, _cb)(void)

# define Z_ADD_TEST(_name, _group, _cb)                                      \
    groups[#_group].push_back((z_test_t){                           \
                .name = _name, .test_cb = Z_TEST_NAME(_group, _cb)      \
   })

# define Z_GROUP(_name, _desc)                                               \
    static void init_##_name(std::string desc=_desc)

#define Z_GROUP_INIT(_name) init_##_name()

#undef Z_TEST_NAME

#endif
