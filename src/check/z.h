#ifndef Z_H_
# define Z_H_

# include <iostream>
# include <stdio.h>

typedef struct dlist_t dlist_t;
struct dlist_t {
    dlist_t *next;
};

typedef struct {
    dlist_t *list;
    std::string name;
    bool (*test_cb)(void);
} z_test_t;

typedef struct {
    dlist_t    *list;
    std::string name;
    z_test_t   *tests;
} z_group_t;

typedef z_test_t Test;
typedef z_group_t Group;

extern Group *groups;

# define DLIST_APPEND(list1, list2)                                          \
    do {                                                                     \
        ((dlist_t *)&list2)->next = ((dlist_t * )&list1)->next;              \
        ((dlist_t *)&list1)->next = ((dlist_t *)(&list2));                   \
    } while (0)

# define dlist_for_each(_type, _cur, _dlist)                                 \
    for (_type *_cur = (_type *)_dlist; _cur; _cur = (_type *)_cur->list)


# define Z_ASSERT(expr)                                                      \
    if (!(expr)) {                                                           \
        std::cerr << "Test " << __func__ << ": " #expr " failed at line "    \
                  << __LINE__ << std::endl;                                  \
        return false;                                                        \
    }

# define Z_ASSERT_EQ(expr1, expr2)                                           \
    if ((expr1) != (expr2)) {                                                \
        std::cerr << "Test " << __func__ << ": `" << (expr1)                 \
                  << "` not equal to `" << (expr2) << "` at line "           \
                  << __LINE__ << std::endl;                                  \
        return false;                                                        \
    }
# define Z_ASSERT_NEQ(expr1, expr2)                                          \
    if ((expr1) == (expr2)) {                                                \
        std::cerr << "Test " << __func__ << ": `" << (expr1)                 \
                  << "` equal to `" << (expr2) << "` at line "               \
                  << __LINE__ << std::endl;                                  \
        return false;                                                        \
    }


# define Z_TEST_NAME(_name) z_##_name

# define Z_TEST(_name, _desc)                                                \
    static bool Z_TEST_NAME(_name)(void);                                    \
    static z_test_t z_test_##_name = (z_test_t){                             \
        .list = NULL,                                                        \
        .name = #_name,                                                      \
        .test_cb = Z_TEST_NAME(_name),                                       \
    };                                                                       \
    __attribute__((constructor))                                             \
    static void z_test_##_name##_init(void) {                                \
        printf("%s\n", __func__);                                            \
        DLIST_APPEND(groups->tests, z_test_##_name);                         \
    }                                                                        \
    static bool Z_TEST_NAME(_name)(void) {

# define Z_TEST_END  return true; }

# define Z_TEST_RAND(_name, _desc, _time)                                    \
    Z_TEST(_name, _desc)                                                     \
    for (int _z_rand_time = 0; _z_rand_time < _time; _z_rand_time++)



# define Z_GROUP(_name, _desc)                                               \
    static z_group_t z_group_##_name = {                                     \
        .list = NULL,                                                        \
        .name = #_name,                                                      \
        .tests = NULL,                                                       \
    };                                                                       \
    __attribute__((constructor))                                             \
    static void init_##_name(std::string desc=_desc) {                       \
        printf("%s - %s\n", __func__, #_name);                               \
        ((dlist_t *)&z_group_##_name)->next = ((dlist_t *)groups);           \
        groups = &z_group_##_name;                                           \
    }                                                                        \
    namespace z_group_##name


#endif /* !Z_H_ */
