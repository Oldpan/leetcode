//
// Created by 郭彦宗 on 2019-07-03.
//

#include "test_concepts.h"
#include "../DataStructure/linearlist.h"

int test_add(int a, int b)
{
    if(a <= 0 || b <= 0)
        throw illegalParameterValue("test example input data invalid!");
    else
        return a + b;
}

int test_throw()
{
    try {cout << test_add(3,0) << endl;}
    catch (illegalParameterValue e)
    {
        cout << "The parameters are not right!" << endl;
        e.outputMessage();
        return 1;
    }
}

// 这个函数用于申请动态的二维数组空间，
// 但是没有错误检查，也就是说我们在申请空间的时候应该try catch一下
template <class T>
void make2Darray(T ** &x, int row, int col)
{
    // 创建行指针
    x = new T * [row];

    // 为每一行分配空间
    for (int i = 0; i < row; i ++)
        x[i] = new T [col];
}

// 只有指向动态分配的对象的指针才能交给 shared_ptr 对象托管。将指向普通局部变量、全局变量的指针交给 shared_ptr 托管，
// 编译时不会有问题，但程序运行时会出错，因为不能析构一个并没有指向动态分配的内存空间的指针。
void test_shared_ptr()
{
    shared_ptr<A> sp1(new A(2));  //A(2)由sp1托管，
    shared_ptr<A> sp2(sp1);       //A(2)同时交由sp2托管
    shared_ptr<A> sp3;
    sp3 = sp2;                    //A(2)同时交由sp3托管
    cout << sp1->i << "," << sp2->i <<"," << sp3->i << endl;
    A * p = sp3.get();             // get返回托管的指针，p 指向 A(2)
    cout << p->i << endl;          //输出 2
    sp1.reset(new A(3));           // reset导致托管新的指针, 此时sp1托管A(3)
    sp2.reset(new A(4));           // sp2托管A(4)
    cout << sp1->i << endl;        //输出 3
    sp3.reset(new A(5));            // sp3托管A(5),A(2)无人托管，被delete
    cout << "end" << endl;

    // 注意，不能用以下的方法去初始化指针 sp1 和 sp2 并不会共享同一个对 p 的托管计数，
    // 而是各自将对 p 的托管计数都记为 1（sp2 无法知道 p 已经被 sp1 托管过）。
    // 这样，当 sp1 消亡时要析构 p，sp2 消亡时要再次析构 p，这会导致程序崩溃。
//    A* p = new A(10);
//    shared_ptr <A> sp1(p), sp2(p);



}