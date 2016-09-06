#include "z.h"


Z_GROUP(test1, "test the Z framework")
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

