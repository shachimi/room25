#include "z.h"

std::vector<z_test_t> groups = std::vector<z_test_t>();

static bool test_bidon(void)
{
    Z_ASSERT(42 == 69);

    return true;
}

Z_GROUP(test, "test the Z framework")
{
    Z_TEST("echec", test_bidon);
}

int main(int argc, char **argv)
{
    int i = 0;
    int nb_failed = 0, nb_success = 0;

    init_test();

    while (i < groups.size()) {
        std::cout << "Test `" << groups[i].name << "`:";
        if (groups[i].test_cb()) {
            std::cout << " Ok" << std::endl;
            nb_success++;
        } else {
            std::cout << " Failed" << std::endl;
            nb_failed++;
        }
        i++;
    }

    std::cout << "Results:\n\t"
              << nb_success << " succeed\n\t"
              << nb_failed << " failed\n";

    return 0;
}
