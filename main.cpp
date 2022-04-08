#include "ft_vector.hpp"
#include <iostream>

#include "gtest/gtest.h"

TEST(ft_vector_test, testDefConstr)
{
    ft::vector<int> v;
    ASSERT_TRUE(v.size() == 0);
    ASSERT_TRUE(v.capacity() == 1);
}

TEST(ft_vector_test, testConstrElemN)
{
    ft::vector<int> v(5, 443);
    ASSERT_TRUE(v.size() == 5);
    ASSERT_TRUE(v.capacity() == 6);
    ASSERT_TRUE(v.at(0) == 443);
    ASSERT_TRUE(v.at(1) == 443);
    ASSERT_TRUE(v.at(2) == 443);
    ASSERT_TRUE(v.at(3) == 443);
    ASSERT_TRUE(v.at(4) == 443);
}

TEST(ft_vector_test, testConstrCopy)
{
    ft::vector<int> vt(5, 443);
    ft::vector<int> v(vt);

    ASSERT_TRUE(v.size() == 5);
    ASSERT_TRUE(v.capacity() == 6);
    ASSERT_TRUE(v.at(0) == 443);
    ASSERT_TRUE(v.at(1) == 443);
    ASSERT_TRUE(v.at(2) == 443);
    ASSERT_TRUE(v.at(3) == 443);
    ASSERT_TRUE(v.at(4) == 443);
}

TEST(ft_vector_test, testAt)
{
    ft::vector<int> v(5, 443);

    ASSERT_TRUE(v.at(0) == 443);
    ASSERT_TRUE(v.at(1) == 443);
    ASSERT_TRUE(v.at(2) == 443);
    ASSERT_TRUE(v.at(3) == 443);
    ASSERT_TRUE(v.at(4) == 443);

    ASSERT_THROW(v.at(-1), std::out_of_range);
    ASSERT_THROW(v.at(5), std::out_of_range);
    ASSERT_THROW(v.at(5555), std::out_of_range);
}

TEST(ft_vector_test, testOperatorIndex)
{
    ft::vector<int> v(5, 443);

    ASSERT_TRUE(v[0] == 443);
    ASSERT_TRUE(v[1] == 443);
    ASSERT_TRUE(v[2] == 443);
    ASSERT_TRUE(v[3] == 443);
    ASSERT_TRUE(v[4] == 443);
}

TEST(ft_vector_test, testOperatorAssign)
{
    ft::vector<int> vt(5, 443);
    ft::vector<int> v;
    v = vt;
    v = v;

    ASSERT_TRUE(v[0] == 443);
    ASSERT_TRUE(v[1] == 443);
    ASSERT_TRUE(v[2] == 443);
    ASSERT_TRUE(v[3] == 443);
    ASSERT_TRUE(v[4] == 443);
    ASSERT_TRUE(v.size() == vt.size());
    ASSERT_TRUE(v.capacity() == vt.capacity());
}

TEST(ft_vector_test, testResize)
{
    ft::vector<int> v;

    // set some initial content:
    for (int i = 1; i < 10; i++)
        v.push_back(i);

    v.resize(5);
    v.resize(8, 100);
    v.resize(12);

    ASSERT_TRUE(v[0] == 1);
    ASSERT_TRUE(v[1] == 2);
    ASSERT_TRUE(v[2] == 3);
    ASSERT_TRUE(v[3] == 4);
    ASSERT_TRUE(v[4] == 5);
    ASSERT_TRUE(v[5] == 100);
    ASSERT_TRUE(v[6] == 100);
    ASSERT_TRUE(v[7] == 100);
    ASSERT_TRUE(v[8] == 0);
    ASSERT_TRUE(v[9] == 0);
    ASSERT_TRUE(v[10] == 0);
    ASSERT_TRUE(v[11] == 0);
    ASSERT_TRUE(v.size() == 12);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
