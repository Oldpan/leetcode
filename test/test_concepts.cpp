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