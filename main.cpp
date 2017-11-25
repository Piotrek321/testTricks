#include "tst_yes.h"
#include "tst_test1.h"

#include <gtest/gtest.h>
#include <math.h>


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
