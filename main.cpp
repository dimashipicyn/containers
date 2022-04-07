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


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    //std::cout << "Hello, world!\n";
    /*
    char s[100];

    scanf("%s", s);

    size_t len = strlen(s);
    for (size_t i = 0; i < len; ++i) {
        printf("s index = %u; val = %d\n", i, (unsigned char)s[i]);
    }

    int isPalindrome = 1;
    for (size_t i = 0; i < len / 2; ++i) {
        unsigned char first = (unsigned char)s[i];
        unsigned char second = (unsigned char)s[len - 1 - i];
        if (first != second) {
            isPalindrome = 0;
            break;
        }
    }

    if (isPalindrome) {
        printf("Palindrom!\n");
    }
    else {
        printf("No palindrom!\n");
    }
    */
}
