
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

TEST(UtilityTest, TestExpansion)
{
    // FIXME it shouldn't be /home/scott
    const char* original = "~/is/the/best";
    const char* expected = "/home/scott/is/the/best";

    char* result = 0;

    EXPECT_EQ(true, expand_path(original, &result));
    EXPECT_EQ(0, strcmp(expected, result));
}

TEST(UtilityTest, TestAlphanumeric)
{

    const char* a = "abcDEF123";
    const char* b = "abc-dEf123";
    const char* c = "-abc";
    const char* d = "abc-";
    const char* e = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmopqrstuvwxyz1234567890";
    char* result = 0;

    EXPECT_EQ(true, is_alphanumeric(a));
    EXPECT_EQ(false, is_alphanumeric(b));
    EXPECT_EQ(false, is_alphanumeric(c));
    EXPECT_EQ(false, is_alphanumeric(d));
    EXPECT_EQ(true, is_alphanumeric(e));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
