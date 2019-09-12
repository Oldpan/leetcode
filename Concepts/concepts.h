//
// Created by prototype on 18-12-17.
//

#ifndef PANCNN_CONCEPTS_H
#define PANCNN_CONCEPTS_H

#include <iostream>
#include <vector>
#include <memory>
#include <exception>

using namespace std;

/*static_cast 告诉编译器 这样的类型转换是已知的，不需要警告*/
//union U { int a; double b; } u;
//void* x = &u;                        // x's value is "pointer to u"
//double* y = static_cast<double*>(x); // y's value is "pointer to u.b"
//char* z = static_cast<char*>(x);     // z's value is "pointer to u"

// 元编程可以在编译期检查一些可以避免的错误,比如输入值的检查


/*-- forward 的完美转发,forward就是 左值还是左值,右值还是右值--*/
//template<typename T>
//void print(T& t){
//    cout << "lvalue" << endl;
//}
//template<typename T>
//void print(T&& t){
//    cout << "rvalue" << endl;
//}
//
//template<typename T>
//void TestForward(T && v){
//    print(v);
//    print(std::forward<T>(v));
//    print(std::move(v));
//}



/*--- const usage ----*/
//float pii = 3.1415926;
//const float pi = 3.1415926;
//const float *pp = &pi;    // pointer to const
//float *const ppp = &pii;   // const point   can't do this: float *const ppp = &pi
//const float *const pppp = &pi;



/*在C++中类的对象建立分为两种，一种是静态建立，如A a；
 * 另一种是动态建立，如A* p=new A()，A*p=(A*)malloc()；
 * 静态建立一个类对象，是由编译器为对象在栈空间中分配内存，通过直接移动栈顶指针挪出适当的空间，
 * 然后在这片内存空间上调用构造函数形成一个栈对象。动态建立类对象，
 * 是使用new运算符将对象建立在堆空间中，在栈中只保留了指向该对象的指针。
 * 栈是由编译器自动分配释放 ，存放函数的参数值，局部变量的值，对象的引用地址等。
 * 其操作方式类似于数据结构中的栈，通常都是被调用时处于存储空间中，调用完毕立即释放。
 * 堆中通常保存程序运行时动态创建的对象，C++堆中存放的对象需要由程序员分配释放，它存在程序运行的整个生命期，直到程序结束由OS释放。 */



/*--C++对定义于　不同编译单元内的non-local static对象　的初始化次序并无明确定义*/
//class FileSystem{
//public:
//    FileSystem() = default;
//    std::size_t numDisks() const;
//};
//
//FileSystem& tfs()
//{
//    static FileSystem fs;
//    return fs;
//}










#endif //PANCNN_CONCEPTS_H


