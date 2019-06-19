//
// Created by 郭彦宗 on 2019-06-19.
//

#include "test_arraylist.h"


void test_init_arraylist()
{
    linearLIst<int> *x = (linearLIst<int>) new arrayList<int>(100);
    arrayList<double> y(100);
    arrayList<char> z;
    arrayList<double> w(y);

}

