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


/*------------------链表-----------------*/
template <class T>
chain<T>::chain(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << "Must be > 0";
        throw illegalParameterValue(s.str());
    }
    firstNode = NULL;
    listSize = 0;
}

template <class T>
chain<T>::chain(const chain<T> & theList)
{ // 复制构造函数
    listSize = theList.listSize;

    if(listSize == 0)
    {
        firstNode = NULL;
        return ;
    }

    chainNode<T>* sourceNode = theList.firstNode;
    firstNode = new chainNode<T>(sourceNode->element);
    // 复制链表的首元素
    sourceNode = sourceNode->next;
    chainNode<T>* targetNode = firstNode;
    // 当前链表 *this 的最后一个元素
    while (sourceNode != NULL)
    {// 复制剩余元素
        targetNode->next = new chainNode<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->next = NULL;
}

template <class T>
chain<T>::~chain()
{
    // 链表析构函数，删除链表的所有节点
    while (firstNode != NULL)
    {// 删除首节点
        chainNode<T>* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template <class T>
T& chain<T>::get(int theIndex) const
{
    checkIndex(theIndex);

    chainNode<T>* currentNode = firstNode;
    for(int i = 0; i < theIndex; i ++)
        currentNode = currentNode->next;
    return currentNode->element;
}

template <class T>
int chain<T>::indexOf(const T &theElement) const
{
    chainNode<T>* currentNode = firstNode;
    int index = 0;
    while (currentNode != NULL &&
           currentNode->element != theElement)
    {
        // 移向下一个节点
        currentNode = currentNode->next;
        index++;
    }
    // 确定是否找到所需的元素
    if(currentNode == NULL)
        return -1;
    else
        return index;
}

// 删除元素有三种情况 1、无效索引 2、删除空表的第0个元素 3、删除其他节点的元素
template <class T>
void chain<T>::erase(int theIndex)
{
    checkIndex(theIndex);

    chainNode<T>* deleteNode;
    if(theIndex == 0)
    {
        deleteNode = firstNode;
        firstNode = firstNode->next;
    } else
    {// 用指针p指向要删除节点的前驱节点
        chainNode<T>* p = firstNode;
        for(int i = 0; i < theIndex - 1; i ++)
            p = p->next;
        deleteNode = p->next;
        p->next = p->next->next;     // 删除deleteNode指向的节点
    }
    listSize --;
    delete deleteNode;
}

// 插入元素和删除元素类型，为了在链表中索引为theIndex的位置上插入一个新元素，需要
// 首先找到索引为theIndex-1的元素节点，然后在该节点之后插入新元素节点。
template <class T>
void chain<T>::insert(int theIndex, const T &theElement)
{
    if(theIndex < 0 || theIndex > listSize)
    {// 无效索引
        ostringstream s;
        s << "index = " << theIndex << "size = " << listSize;
        throw illegalIndex(s.str());
    }

    if(theIndex == 0)
        // 在链表头插入
        firstNode = new chainNode<T>(theElement, firstNode);
    else
    {// 寻找新元素的前缀
        chainNode<T>* p = firstNode;
        for (int i = 0; i < theIndex - 1; i ++)
            p = p->next;
        // 在p之后加入
        p->next = new chainNode<T>(theElement, p->next);
    }
    listSize ++;
}

template <class T>
void chain<T>::output(ostream &out) const
{// 把链表放入输出流
    for (chainNode<T>* currentNode = firstNode;
                       currentNode != NULL;
                       currentNode = currentNode->next)
        out << currentNode->element << " ";
}

template <class T>
ostream& operator<<(ostream& out, const chain<T>& x)
{
    x.output(out);
    return out;
}

//template <class T>
//void extendedChain<T>::clear()
//{
//    while(firstNode != NULL)
//
//
//}

