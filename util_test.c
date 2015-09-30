
#include <stdbool.h>

#include <gtest/gtest.h>

#include "util.h"

TEST(UtilityTest, TestHomeDir1)
{
    EXPECT_EQ(true, is_valid_home_path("/home/scott/.vimrc"));
}

TEST(UtilityTest, TestHomeDir2)
{
    EXPECT_EQ(true, is_valid_home_path("~/.vimrc"));
}

TEST(UtilityTest, TestRootDir1)
{
    EXPECT_EQ(true, is_valid_root_path("/usr/share/slim/themes/xathereal/"));
}

TEST(UtilityTest, TestRootDir2)
{
    EXPECT_EQ(false, is_valid_root_path("~/.vimrc"));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
