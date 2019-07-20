//
// Created by 郭彦宗 on 2019-07-03.
//

#ifndef LEETCODE_TEST_CONCEPTS_H
#define LEETCODE_TEST_CONCEPTS_H

#include <iostream>

class A  // 用于测试shared_ptr的类
{
public:
    int i;
    A(int n):i(n) { };
    ~A() { std::cout << i << " " << "destructed" << std::endl; }
};


int test_throw();
void test_shared_ptr();
void test_max_heap();
void TestSharpedPtr();



#endif //LEETCODE_TEST_CONCEPTS_H
