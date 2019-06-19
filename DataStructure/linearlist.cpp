//
// Created by 郭彦宗 on 2019-06-18.
//

#include <exception>
#include <sstream>
#include <string>
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

// 构造函数
template <class T>
arrayList<T>::arrayList(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        ostringstream s;
        s << "Initial capcity = " << initialCapacity << "must be > 0";
        throw illegalParameterValue(s.str());
    }

    arrayLength = initialCapacity;
    element = new T[arrayLength];
    listSize = 0;
}

template <class T>
arrayList<T>::arrayList(const arrayList<T>& theList)
{
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    element = new T[arrayLength];
    copy(theList.element, theList.element + listSize, element);
}

template <class T>
void arrayList<T>::checkIndex(int index) const
{
    if( index < 0 || index >= listSize)
    {
        ostringstream s;
        s << "index = " << index << "size = " << listSize;
        throw illegalIndex(s.str());
    }
}

template <class T>
T& arrayList<T>::get(int index) const
{
    checkIndex(index);
    return element[index];
}

template <class T>
int arrayList<T>::indexOf(const T &theElement) const
{
    // 返回元素element第一次出现时的索引 所元素不在则返回-1
    int index = (int) (find(element, element + listSize, theElement) - element);

    if(index == listSize)
        return -1;
    else
        return index;
}

template <class T>
void arrayList<T>::erase(int index)
{
    // 删除其索引为index的元素
    // 如果该元素不存在则抛出异常
    checkIndex(index);

    // 利用copy算法把索引从 index+1 index+2 ... listSize-1 的元素向左移动一个位置
    copy(element + index + 1, element + listSize, element + index);

    element[--listSize].~T();
}

// 为什么在空间不够的时候不是 增加1 而是直接将空间加倍呢？ 因为这样会影响连续插入时的渐进时间复杂度
template <class T>
void arrayList<T>::insert(int index, const T &theElement)
{
    // 无效索引
    if(index < 0 || index > listSize)
    {
        ostringstream s;
        s << "index = " << index << "size = " << listSize;
        throw illegalIndex(s.str());
    }

    // 有效索引，确定数组是否已满
    if(listSize == arrayLength)
    {// 数组空间已满，数组长度倍增，方法学习vector的方式
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    // 把元素向右移动一个位置
    copy_backward(element + index, element + listSize,
                  element + listSize + 1);

    element[index] = theElement;
}

template <class T>
void arrayList<T>::output(ostream &out) const
{
    copy(element, element + listSize, ostream_iterator<T>(cout, " "));
}

template <class T>
ostream& operator<<(ostream& out, const arrayList<T>& x)
{
    x.output(out);
    return out;
}


