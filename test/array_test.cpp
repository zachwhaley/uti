#include <gtest/gtest.h>
#include <array.hpp>

TEST(ArrayTest, DefaultConstructor)
{
    uti::Array<int> ar;
    EXPECT_EQ(0, ar.size());
    EXPECT_THROW(ar[0], std::out_of_range);
}

TEST(ArrayTest, lenConstructor)
{
    uti::Array<int> ar(5);
    EXPECT_EQ(5, ar.size());
    EXPECT_NO_THROW(ar[0] = 5);
    EXPECT_EQ(5, ar[0]);
    EXPECT_THROW(ar[5], std::out_of_range);
}

TEST(ArrayTest, CopyConstructor)
{
    uti::Array<int> ar(5);
    ar[0] = 5;
    auto cp = ar;

    EXPECT_EQ(5, cp.size());
    EXPECT_EQ(5, cp[0]);
    EXPECT_THROW(cp[5], std::out_of_range);
}

TEST(ArrayTest, MoveConstructor)
{
    uti::Array<int> ar(5);
    ar[0] = 5;
    auto mv = std::move(ar);

    EXPECT_EQ(0, ar.size());
    EXPECT_THROW(ar[0], std::out_of_range);

    EXPECT_EQ(5, mv.size());
    EXPECT_EQ(5, mv[0]);
    EXPECT_THROW(mv[5], std::out_of_range);
}

TEST(ArrayTest, InitializerListConstructor)
{
    uti::Array<int> ar = { 1, 2, 3 };

    EXPECT_EQ(3, ar.size());
    EXPECT_EQ(1, ar[0]);
    EXPECT_EQ(2, ar[1]);
    EXPECT_EQ(3, ar[2]);
    EXPECT_THROW(ar[3], std::out_of_range);
}

TEST(ArrayTest, AssignmentOperator)
{
    uti::Array<int> ar = { 1, 2, 3 };
    uti::Array<int> ra;

    EXPECT_EQ(3, ar.size());
    EXPECT_EQ(0, ra.size());

    ra = ar;

    EXPECT_EQ(3, ar.size());
    EXPECT_EQ(3, ra.size());
    EXPECT_EQ(1, ra[0]);
    EXPECT_EQ(2, ra[1]);
    EXPECT_EQ(3, ra[2]);
    EXPECT_THROW(ra[3], std::out_of_range);
}

TEST(ArrayTest, Iterators)
{
    uti::Array<int> ar = { 1, 2, 3 };
    int v = 1;
    for (auto it = ar.begin(); it != ar.end(); it++) {
        EXPECT_EQ(v, *it);
        v++;
    }
}

TEST(ArrayTest, Ranges)
{
    uti::Array<int> ar = { 1, 2, 3 };
    int v = 1;
    for (auto i : ar) {
        EXPECT_EQ(v, i);
        v++;
    }
}
