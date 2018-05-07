#include "z.h"

#if 0
Z_GROUP(test, "test the Z framework")
{
    Z_TEST(test1, bidon)
    {
        Z_ASSERT(42 == 69);

        return true;
    }

    Z_TEST(test2, success)
    {
        Z_ASSERT(true);

        return true;
    }
}
#endif

int main(int argc, char **argv)
{
    int i = 0;
    int nb_failed = 0, nb_success = 0;

    dlist_for_each(z_group_t, group, groups) {
        if (!group->tests) {
            continue;
        }
        std::cout << "Group: `" << group->name << "`" << std::endl;
        dlist_for_each(z_test_t, test, group->tests) {
            std::cout << "  Tests `" << test->name << "`: ";
            if (test->test_cb()) {
                std::cout << "Ok" << std::endl;
                nb_success++;
            } else {
                std::cout << "Failed" << std::endl;
                nb_failed++;
            }
        }
    }

    std::cout << "Results:\n\t"
              << nb_success << " succeed\n\t"
              << nb_failed << " failed\n";

    return 0;
}
