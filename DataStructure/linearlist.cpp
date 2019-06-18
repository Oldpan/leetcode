//
// Created by 郭彦宗 on 2019-06-18.
//

#include <exception>
#include "linearlist.h"

template <class T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
    if(newLength < 0)
        throw ;

    T* temp = new T(newLength);
    int number = min(oldLength, newLength);
    copy(a, a + number, temp);
    delete [] a;
    a = temp;
}
