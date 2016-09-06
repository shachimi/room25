#include "z.h"

GroupMap groups;

Z_TEST(test, bidon)
{
    Z_ASSERT(42 == 69);

    return true;
}

Z_GROUP(test, "test the Z framework")
{
    Z_ADD_TEST("echec", test, bidon);
}

int main(int argc, char **argv)
{
    int i = 0;
    int nb_failed = 0, nb_success = 0;

    Z_GROUP_INIT(test);

    for (GroupMap::iterator map_it = groups.begin();
         map_it != groups.end(); map_it++) {
        Group group;

        std::cout << "Group `" << map_it->first << "`:" << std::endl;

        for (Group::iterator group_it = map_it->second.begin();
             group_it != map_it->second.end(); group_it++) {
            std::cout << "Test `" << (*group_it).name << "`:";
            if ((*group_it).test_cb()) {
                std::cout << " Ok" << std::endl;
                nb_success++;
            } else {
                std::cout << " Failed" << std::endl;
                nb_failed++;
            }
        }
    }

    std::cout << "Results:\n\t"
              << nb_success << " succeed\n\t"
              << nb_failed << " failed\n";

    return 0;
}
