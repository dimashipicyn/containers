#include "vector.h"
#include "stack.h"
#include "btree.h"
#include <iostream>

#include "gtest/gtest.h"

//#define ft std

TEST(ft_vector_test, testDefConstr)
{
    ft::vector<int> v;
    ASSERT_TRUE(v.size() == 0);
    ASSERT_TRUE(v.capacity() == 0);
}

TEST(ft_vector_test, testConstrElemN)
{
    ft::vector<int> v(5, 443);
    ASSERT_TRUE(v.size() == 5);
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

    ASSERT_TRUE(v.capacity() == 12);
    // set some initial content:
    for (int i = 0; i < 5; i++)
        v.push_back(i);
    
    v.shrink_to_fit();
    ASSERT_TRUE(v.capacity() < 12);
}

TEST(ft_vector_test, testFrontBack)
{
    ft::vector<int> v;

    v.push_back(111);
    v.push_back(12345);
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
    // ft::vector<int> iv;
    // ft::vector<const int> civ;
    // ft::vector<int*> piv;
    // ft::vector<const int*> cpiv;
    // ft::vector<int const*> pciv;
    // ft::vector<std::reference_wrapper<int>> riv;
    // ft::vector<std::reference_wrapper<const int>> criv;
}

void f(int* a) {
    std::cout << *a << "\n";
}
bool cmp(int* a, int* b) {
    return *a < *b;
}
TEST(ft_vector_test, testIterator)
{

}

TEST(ft_vector_test, testInsert1_1) {
    ft::vector<std::string> v;

    v.push_back("hello");
    v.push_back("world");
    v.push_back("tester");

    ft::vector<std::string>::iterator pos = v.insert(v.begin(), "petuh");

    ASSERT_TRUE(*pos == "petuh");
    
    ASSERT_TRUE(v[0] == "petuh");
    ASSERT_TRUE(v[1] == "hello");
    ASSERT_TRUE(v[2] == "world");
    ASSERT_TRUE(v[3] == "tester");
}

TEST(ft_vector_test, testInsert1_2) {
    ft::vector<std::string> v;

    v.push_back("hello");
    v.push_back("world");
    v.push_back("tester");

    ft::vector<std::string>::iterator pos = v.insert(v.begin() + 1, "petuh");

    ASSERT_TRUE(*pos == "petuh");
    
    ASSERT_TRUE(v[0] == "hello");
    ASSERT_TRUE(v[1] == "petuh");
    ASSERT_TRUE(v[2] == "world");
    ASSERT_TRUE(v[3] == "tester");
}

TEST(ft_vector_test, testInsert1_3) {
    ft::vector<std::string> v;

    v.push_back("hello");
    v.push_back("world");
    v.push_back("tester");

    ft::vector<std::string>::iterator pos = v.insert(v.begin() + 2, "petuh");

    ASSERT_TRUE(*pos == "petuh");
    
    ASSERT_TRUE(v[0] == "hello");
    ASSERT_TRUE(v[1] == "world");
    ASSERT_TRUE(v[2] == "petuh");
    ASSERT_TRUE(v[3] == "tester");
}

TEST(ft_vector_test, testInsert1_4) {
    ft::vector<std::string> v;

    v.push_back("hello");
    v.push_back("world");
    v.push_back("tester");

    ft::vector<std::string>::iterator pos = v.insert(v.begin() + 3, "petuh");

    ASSERT_TRUE(*pos == "petuh");
    
    ASSERT_TRUE(v[0] == "hello");
    ASSERT_TRUE(v[1] == "world");
    ASSERT_TRUE(v[2] == "tester");
    ASSERT_TRUE(v[3] == "petuh");
}

TEST(ft_vector_test, testInsert1_5) {
    ft::vector<std::string> v;
    ft::vector<std::string> vv;

    ft::vector<std::string>::iterator pos1 = v.insert(v.begin(), "petuh");
    ft::vector<std::string>::iterator pos2 = vv.insert(vv.end(), "petuh");

    ASSERT_TRUE(*pos1 == "petuh");
    ASSERT_TRUE(*pos2 == "petuh");
    
    ASSERT_TRUE(v[0] == "petuh");
    ASSERT_TRUE(vv[0] == "petuh");
}

TEST(ft_vector_test, testInsert_2_1) {
    ft::vector<std::string> v;

    v.push_back("hello");
    v.push_back("world");
    v.push_back("tester");

    ft::vector<std::string>::iterator pos = v.insert(v.begin(), 3, "petuh");

    ASSERT_TRUE(*pos == "petuh");
    ASSERT_TRUE(*(pos+1) == "petuh");
    ASSERT_TRUE(*(pos+2) == "petuh");
    
    ASSERT_TRUE(v[0] == "petuh");
    ASSERT_TRUE(v[1] == "petuh");
    ASSERT_TRUE(v[2] == "petuh");
    ASSERT_TRUE(v[3] == "hello");
    ASSERT_TRUE(v[4] == "world");
    ASSERT_TRUE(v[5] == "tester");
}

TEST(ft_vector_test, testInsert2_2) {
    ft::vector<std::string> v;

    v.push_back("hello");
    v.push_back("world");
    v.push_back("tester");

    ft::vector<std::string>::iterator pos = v.insert(v.begin() + 1, 3, "petuh");

    ASSERT_TRUE(*pos == "petuh");
    ASSERT_TRUE(*(pos+1) == "petuh");
    ASSERT_TRUE(*(pos+2) == "petuh");
    
    ASSERT_TRUE(v[0] == "hello");
    ASSERT_TRUE(v[1] == "petuh");
    ASSERT_TRUE(v[2] == "petuh");
    ASSERT_TRUE(v[3] == "petuh");
    ASSERT_TRUE(v[4] == "world");
    ASSERT_TRUE(v[5] == "tester");
}

TEST(ft_vector_test, testInsert2_3) {
    ft::vector<std::string> v;

    v.push_back("hello");
    v.push_back("world");
    v.push_back("tester");

    ft::vector<std::string>::iterator pos = v.insert(v.begin() + 2, 3, "petuh");

    ASSERT_TRUE(*pos == "petuh");
    ASSERT_TRUE(*(pos+1) == "petuh");
    ASSERT_TRUE(*(pos+2) == "petuh");
    
    ASSERT_TRUE(v[0] == "hello");
    ASSERT_TRUE(v[1] == "world");
    ASSERT_TRUE(v[2] == "petuh");
    ASSERT_TRUE(v[3] == "petuh");
    ASSERT_TRUE(v[4] == "petuh");
    ASSERT_TRUE(v[5] == "tester");
}

TEST(ft_vector_test, testInsert2_4) {
    ft::vector<std::string> v;

    v.push_back("hello");
    v.push_back("world");
    v.push_back("tester");

    ft::vector<std::string>::iterator pos = v.insert(v.begin() + 3, 3, "petuh");

    ASSERT_TRUE(*pos == "petuh");
    ASSERT_TRUE(*(pos+1) == "petuh");
    ASSERT_TRUE(*(pos+2) == "petuh");
    
    ASSERT_TRUE(v[0] == "hello");
    ASSERT_TRUE(v[1] == "world");
    ASSERT_TRUE(v[2] == "tester");
    ASSERT_TRUE(v[3] == "petuh");
    ASSERT_TRUE(v[4] == "petuh");
    ASSERT_TRUE(v[5] == "petuh");
}

TEST(ft_vector_test, testInsert2_5) {
    ft::vector<std::string> v;
    ft::vector<std::string> vv;

    ft::vector<std::string>::iterator pos1 = v.insert(v.begin(), 3, "petuh");
    ft::vector<std::string>::iterator pos2 = vv.insert(vv.end(), 3, "petuh");

    ASSERT_TRUE(*pos1 == "petuh");
    ASSERT_TRUE(*(pos1+1) == "petuh");
    ASSERT_TRUE(*(pos1+2) == "petuh");
    
    ASSERT_TRUE(*pos2 == "petuh");
    ASSERT_TRUE(*(pos2+1) == "petuh");
    ASSERT_TRUE(*(pos2+2) == "petuh");
    
    ASSERT_TRUE(v[0] == "petuh");
    ASSERT_TRUE(v[1] == "petuh");
    ASSERT_TRUE(v[2] == "petuh");
    
    ASSERT_TRUE(vv[0] == "petuh");
    ASSERT_TRUE(vv[1] == "petuh");
    ASSERT_TRUE(vv[2] == "petuh");
}

TEST(ft_vector_test, testInsert_3_1) {
    ft::vector<std::string> v;
    ft::vector<std::string> vw;

    v.push_back("hello");
    v.push_back("world");
    v.push_back("tester");
    
    vw.push_back("petuh");
    vw.push_back("user");
    vw.push_back("loh");

    ft::vector<std::string>::iterator pos = v.insert(v.begin(), vw.begin(), vw.end());

    ASSERT_TRUE(*pos == "petuh");
    ASSERT_TRUE(*(pos+1) == "user");
    ASSERT_TRUE(*(pos+2) == "loh");
    
    ASSERT_TRUE(v[0] == "petuh");
    ASSERT_TRUE(v[1] == "user");
    ASSERT_TRUE(v[2] == "loh");
    ASSERT_TRUE(v[3] == "hello");
    ASSERT_TRUE(v[4] == "world");
    ASSERT_TRUE(v[5] == "tester");
}

TEST(ft_vector_test, testInsert3_2) {
    ft::vector<std::string> v;
    ft::vector<std::string> vw;

    v.push_back("hello");
    v.push_back("world");
    v.push_back("tester");
    
    vw.push_back("petuh");
    vw.push_back("user");
    vw.push_back("loh");

    ft::vector<std::string>::iterator pos = v.insert(v.begin() + 1, vw.begin(), vw.end());

    ASSERT_TRUE(*pos == "petuh");
    ASSERT_TRUE(*(pos+1) == "user");
    ASSERT_TRUE(*(pos+2) == "loh");
    
    ASSERT_TRUE(v[0] == "hello");
    ASSERT_TRUE(v[1] == "petuh");
    ASSERT_TRUE(v[2] == "user");
    ASSERT_TRUE(v[3] == "loh");
    ASSERT_TRUE(v[4] == "world");
    ASSERT_TRUE(v[5] == "tester");
}

TEST(ft_vector_test, testInsert3_3) {
    ft::vector<std::string> v;
    ft::vector<std::string> vw;

    v.push_back("hello");
    v.push_back("world");
    v.push_back("tester");
    
    vw.push_back("petuh");
    vw.push_back("user");
    vw.push_back("loh");

    ft::vector<std::string>::iterator pos = v.insert(v.begin() + 2, vw.begin(), vw.end());

    ASSERT_TRUE(*pos == "petuh");
    ASSERT_TRUE(*(pos+1) == "user");
    ASSERT_TRUE(*(pos+2) == "loh");
    
    ASSERT_TRUE(v[0] == "hello");
    ASSERT_TRUE(v[1] == "world");
    ASSERT_TRUE(v[2] == "petuh");
    ASSERT_TRUE(v[3] == "user");
    ASSERT_TRUE(v[4] == "loh");
    ASSERT_TRUE(v[5] == "tester");
}

TEST(ft_vector_test, testInsert3_4) {
    ft::vector<std::string> v;
    ft::vector<std::string> vw;

    v.push_back("hello");
    v.push_back("world");
    v.push_back("tester");
    
    vw.push_back("petuh");
    vw.push_back("user");
    vw.push_back("loh");

    ft::vector<std::string>::iterator pos = v.insert(v.begin() + 3, vw.begin(), vw.end());

    ASSERT_TRUE(*pos == "petuh");
    ASSERT_TRUE(*(pos+1) == "user");
    ASSERT_TRUE(*(pos+2) == "loh");
    
    ASSERT_TRUE(v[0] == "hello");
    ASSERT_TRUE(v[1] == "world");
    ASSERT_TRUE(v[2] == "tester");
    ASSERT_TRUE(v[3] == "petuh");
    ASSERT_TRUE(v[4] == "user");
    ASSERT_TRUE(v[5] == "loh");
}

TEST(ft_vector_test, testInsert3_5) {
    ft::vector<std::string> v;
    ft::vector<std::string> vv;
    ft::vector<std::string> vw;
    
    vw.push_back("petuh");
    vw.push_back("user");
    vw.push_back("loh");

    ft::vector<std::string>::iterator pos1 = v.insert(v.begin(), vw.begin(), vw.end());
    ft::vector<std::string>::iterator pos2 = vv.insert(vv.end(), vw.begin(), vw.end());

    ASSERT_TRUE(*pos1 == "petuh");
    ASSERT_TRUE(*(pos1+1) == "user");
    ASSERT_TRUE(*(pos1+2) == "loh");
    
    ASSERT_TRUE(*pos2 == "petuh");
    ASSERT_TRUE(*(pos2+1) == "user");
    ASSERT_TRUE(*(pos2+2) == "loh");
    
    ASSERT_TRUE(v[0] == "petuh");
    ASSERT_TRUE(v[1] == "user");
    ASSERT_TRUE(v[2] == "loh");
    
    ASSERT_TRUE(vv[0] == "petuh");
    ASSERT_TRUE(vv[1] == "user");
    ASSERT_TRUE(vv[2] == "loh");
}

TEST(ft_vector_test, TestKek) {
    ft::vector<std::string> v;
    v.push_back(std::string("hello"));
    v.push_back(std::string("world"));
    v.push_back(std::string("tester"));

    std::vector<std::string> vv;

    vv.insert(vv.end(), v.begin(), v.end());
    
    ASSERT_TRUE(vv[0] == "hello");
    ASSERT_TRUE(vv[1] == "world");
    ASSERT_TRUE(vv[2] == "tester");
}

TEST(ft_vector_test, test_is_integral) {
    ASSERT_TRUE(ft::is_integral<int>::value == true);
    ASSERT_TRUE(ft::is_integral<float>::value == false);
}

TEST(ft_vector_test, testIteratorConstr) {
    ft::vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    ft::vector<int> vw(v.begin(), v.end());

    ASSERT_TRUE(vw[0] == 1);
    ASSERT_TRUE(vw[1] == 2);
    ASSERT_TRUE(vw[2] == 3);
    ASSERT_TRUE(vw[3] == 4);
    ASSERT_TRUE(vw[4] == 5);
}

TEST(ft_stack_test, testConstruct) {
    ft::stack<int> v;

    v.push(1);
    v.push(2);
    v.push(3);
    v.push(4);
    v.push(5);

    ft::stack<int> v1;

    v.push(1);
    v.push(2);
    v.push(3);
    v.push(4);
    v.push(5);

    //ASSERT_TRUE(v == v1);
}

TEST(ft_btree_test, test) {
    Btree<int> tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(4);
    tree.insert(6);
    
    ASSERT_TRUE(tree.find(4) != nullptr);
    ASSERT_TRUE(tree.find(4)->value == 4);
    
    ASSERT_TRUE(tree.find(6) != nullptr);
    ASSERT_TRUE(tree.find(6)->value == 6);
    tree.prefix();
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
