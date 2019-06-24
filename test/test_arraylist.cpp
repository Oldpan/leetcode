//
// Created by 郭彦宗 on 2019-06-19.
//

#include "test_arraylist.h"


void test_init_arraylist()
{
//    linearLIst<int> *x = (linearLIst<int>) new arrayList<int>(100);
//    arrayList<double> y(100);
//    arrayList<char> z;
//    arrayList<double> w(y);

}

void test_init_arraylist_chainnode()
{
    linearLIst<int>* list[10];
    list[0] = new arrayList<int>(20);
    list[1] = new arrayList<int>();
    list[2] = new chain<int>(5);
    list[3] = new chain<int>;
}

void test_common_iterator()
{
    int x[3] = {0,1,2};
    // 用指针y遍历数组x 这个迭代器是随机访问迭代器 是一般的迭代器
    for(int* y = x; y != x+3; y ++)
    {
        cout << *y << endl;
    }
}
