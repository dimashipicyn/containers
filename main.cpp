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

TEST(ft_vector_test, testReserve)
{
    ft::vector<int> v;

    v.reserve(5);

    // set some initial content:
    for (int i = 0; i < 5; i++)
        v.push_back(i);
        
    ASSERT_TRUE(v.capacity() == 5);
    ASSERT_TRUE(v[0] == 0);
    ASSERT_TRUE(v[1] == 1);
    ASSERT_TRUE(v[2] == 2);
    ASSERT_TRUE(v[3] == 3);
    ASSERT_TRUE(v[4] == 4);
    ASSERT_TRUE(v.size() == 5);
    ASSERT_TRUE(v.capacity() == 5);
}

TEST(ft_vector_test, testShrinkToFit)
{
    ft::vector<int> v;

    v.reserve(12);

    // set some initial content:
    for (int i = 0; i < 5; i++)
        v.push_back(i);
    
    ASSERT_TRUE(v.capacity() == 12);
    v.shrink_to_fit();
    ASSERT_TRUE(v.capacity() == 6);
}

TEST(ft_vector_test, testFrontBack)
{
    ft::vector<int> v;

    v.push_back(111);
    v.push_back(222);

    ASSERT_TRUE(v.front() == 111);
    ASSERT_TRUE(v.back() == 222);
}

TEST(ft_vector_test, testPushback)
{
    ft::vector<int> v;
    
    v.push_back(111);
    v.push_back(222);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);

    ASSERT_TRUE(v[0] == 111);
    ASSERT_TRUE(v[1] == 222);
    ASSERT_TRUE(v[2] == 3);
    ASSERT_TRUE(v[3] == 4);
    ASSERT_TRUE(v[4] == 5);
    ASSERT_TRUE(v[5] == 6);
}

TEST(ft_vector_test, testPopback)
{
    ft::vector<int> v;
    
    v.push_back(111);
    v.push_back(222);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);

    ASSERT_TRUE(v.size() == 6);
    v.pop_back();
    v.pop_back();
    ASSERT_TRUE(v.size() == 4);
}

TEST(ft_vector_test, testSwap)
{
    ft::vector<int> v;
    ft::vector<int> vw;

    for (size_t i = 0; i < 5; i++)
    {
        v.push_back(i);
        vw.push_back(4 - i);
    }
    
    v.swap(vw);

    ASSERT_TRUE(v[0] == 4);
    ASSERT_TRUE(v[1] == 3);
    ASSERT_TRUE(v[2] == 2);
    ASSERT_TRUE(v[3] == 1);
    ASSERT_TRUE(v[4] == 0);

    ASSERT_TRUE(vw[0] == 0);
    ASSERT_TRUE(vw[1] == 1);
    ASSERT_TRUE(vw[2] == 2);
    ASSERT_TRUE(vw[3] == 3);
    ASSERT_TRUE(vw[4] == 4);
}

TEST(ft_vector_test, testClear)
{
    ft::vector<int> v;
    for (size_t i = 0; i < 10; i++)
    {
        v.push_back(i);
    }
    v.clear();
    ASSERT_TRUE(v.size() == 0);
}

TEST(ft_vector_test, testOpEqual)
{
    ft::vector<int> v;
    ft::vector<int> vw;
    ft::vector<int> vww;
    for (size_t i = 0; i < 10; i++)
    {
        v.push_back(i);
        vw.push_back(i);
        vww.push_back(i - 1);
    }


    ASSERT_TRUE(v == vw);
    ASSERT_FALSE(v == vww);

    ASSERT_FALSE(v != vw);
    ASSERT_TRUE(v != vww);
}

TEST(ft_vector_test, testOpLess)
{
    ft::vector<int> v;
    ft::vector<int> vw;
    ft::vector<int> vww;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    vw.push_back(1);
    vw.push_back(2);
    vw.push_back(4);

    vww.push_back(1);
    vww.push_back(2);
    vww.push_back(3);

    ASSERT_TRUE(v < vw);
    ASSERT_FALSE(v < vww);
    ASSERT_TRUE(v <= vww);
    vww.push_back(4);
    ASSERT_TRUE(v < vww);
    ASSERT_TRUE(v <= vww);
}

TEST(ft_vector_test, testTypes)
{
    ft::vector<int> iv;
    ft::vector<const int> civ;
    ft::vector<int*> piv;
    ft::vector<const int*> cpiv;
    ft::vector<int const*> pciv;
    ft::vector<std::reference_wrapper<int>> riv;
    ft::vector<std::reference_wrapper<const int>> criv;
}

TEST(ft_vector_test, testIterator)
{
    ft::vector<int> v;
    for (size_t i = 10; i > 0; i--)
    {
        v.push_back(i);
    }
    size_t c = 10;
    for (ft::vector<int>::iterator i = v.begin(); i < v.end(); i++, c--)
    {
        ASSERT_TRUE(*i == c);
    }
    //std::sort(v.begin(), v.end());
    std::iterator_traits<ft::vector_iterator<int>>::value_type;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
