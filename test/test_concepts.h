//
// Created by 郭彦宗 on 2019-07-03.
//

#ifndef LEETCODE_TEST_CONCEPTS_H
#define LEETCODE_TEST_CONCEPTS_H

#include <iostream>

using namespace std;

class A  // 用于测试shared_ptr的类
{
public:
    int i;
    A(int n):i(n) { };
    ~A() { std::cout << i << " " << "destructed" << std::endl; }
};

// 用来测试new操作符的重载
class Test
{
public:

    Test(){ std::cout << "Test()" << std::endl; }

    ~Test(){ std::cout << "~Test()" << std::endl; }

    void show()
    {
        std::cout << "show()" << std::endl;
    }

public:	//new的重载

    void* operator new(size_t size)
    {
        std::cout << "operator new" << std::endl;
        return ::operator new(size);
    }

    void operator delete(void *p)
    {
        std::cout << "operator delete" << std::endl;
        ::operator delete(p);
    }

    void * operator new[](size_t size)
    {
        std::cout << "operator  new[]" << std::endl;
        return ::operator new[](size);
    }

    void operator delete[](void *p)
    {
        std::cout << "operator delete[]" << std::endl;
        return ::operator delete[](p);
    }
};


class Base
{
public:
    Base(){ // 注意构造函数不能定义为虚函数
        cout << "Base construct!" << endl;
    }
    virtual void shout()
    {
        cout << "I am Base!" << endl;
    }
    void shout_warp()
    {
        shout();
    }
    ~Base(){
        cout << "Base deconstruct!" << endl;
    }
};

class Derive: public Base
{
public:
    Derive()
    {
        cout << "Derive construct!" << endl;
    }
    void shout()
    {
        cout << "I am Derive" << endl;
    }
    ~Derive(){
        cout << "Derive deconstruct!" << endl;
    }
};

// 用于测试new与malloc的区别
class TEST
{
private:
    int num1;
    int num2;
public:
    TEST()
    {
        num1 = 10;
        num2 = 20;
    }
    void Print()
    {
        std::cout << num1 << " " << num2 << std::endl;
    }
};


void test_construt_order();
int test_throw();
void test_shared_ptr();
void test_max_heap();
void TestSharpedPtr();
void test_new_operater();
void test_new_and_mal();
void test_vector();
void test_lower_bound();
void test_priority();



#endif //LEETCODE_TEST_CONCEPTS_H
