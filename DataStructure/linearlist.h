#ifndef LEETCODE_LINEARLIST_H
#define LEETCODE_LINEARLIST_H

#include <ostream>
#include <iostream>

using namespace std;

class illegalParameterValue
{
public:
    illegalParameterValue(const string& str):
            message(str){}
    illegalParameterValue(char* theMessage)
    {message = theMessage;}
    void outputMessage() {cout << message << endl;}
private:
    string message;
};

class illegalIndex
{
public:
illegalIndex(string str):
            message(std::move(str)){}
    illegalIndex(char* theMessage)
    {message = theMessage;}
    void outputMessage() {cout << message << endl;}
private:
    string message;
};


template <class T>
class array_iterator
{
public:
    // 用C++的typedef语句实现双向迭代器
    typedef bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;

    // 构造函数
    array_iterator(T* thePosition = 0) { position = thePosition;}

    T& operator*() const { return *position;}
    T* operator->() const {return &*position;}

    // 迭代器的值增加
    array_iterator operator++()
    {++ position; return *this;}

    array_iterator operator++(int)
    {
        array_iterator old = *this;
        ++ position;
        return old;
    }

    // 迭代器的值减小
    array_iterator operator--()
    {
        --position;
        return *this;
    }
    array_iterator operator--(int)
    {
        array_iterator old = *this;
        -- position;
        return old;
    }

    bool operator!= (const array_iterator right) const
    { return position != right.position; }
    bool operator==(const array_iterator right) const
    { return position == right.position; }

protected:
    T* position;                 // 指向表元素的指针
};



// 顺序表、线性表的抽象类 抽象类不能生成具体类
// 其中成员函数之后加上const说明此成员函数不能修改对象的内容
template <class T>
class linearLIst
{
public:
    // 将抽象类的析构函数定位为虚函数的目的是：当一个线性表的示例离开作用域的时候
    // 需要调用的缺省析构函数是引用对象中数据类型的析构函数
    virtual ~linearLIst(){};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& get(int index) const = 0;
    virtual int indexOf(const T& theElement) const = 0;
    virtual void erase(int index) = 0;
    virtual void insert(int index, const T& theElement) = 0;
    virtual void output(ostream& out) const = 0;
};

template <class T>
class extendedLinearList : linearLIst<T>
{
public:
    virtual ~extendedLinearList() {}
    virtual void clear() = 0;
    virtual void push_back(const T& theElement) = 0;
};


template <class T>
class arrayList: public linearLIst<T>
{
public:
    arrayList(int initialCapacity = 10);
    arrayList(const arrayList<T>&);
    ~arrayList() {delete [] element;}

    bool empty() const {return listSize == 0;}
    int size() const {return listSize;}
    T& get(int index) const;
    int indexOf(const T& theElement) const;
    void erase(int index);
    void insert(int index, const T& theElement);
    void output(ostream& out) const;
    int capacity() const {return arrayLength;}

    typedef array_iterator<T> iterator;
    iterator begin() {return iterator(element);}
    iterator end() {return iterator(element + listSize);}

protected:
    void checkIndex(int index) const;
        // 若索引无效 则抛出异常
    T* element;
    int arrayLength;        // 容量
    int listSize;           // 当前的个数

};


// 链表节点的结构定义
template <class T>
struct chainNode
{
    T element;
    chainNode<T> *next;

    chainNode() {}
    chainNode(const T& element)
    {this->element = element;}
    // 因为实例的数据成员与构造函数的形参同名，所以需要使用this这种语法
    chainNode(const T& element, chainNode<T>* next)
    {
        this->element = element;
        this->next = next;
    }
};


template <class T>
class chain_iterator
{
public:
    // 向前迭代器所需要的typedef语句在此省略
    // 构造函数
    chain_iterator(chainNode<T>* theNode = NULL)
    {node = theNode;}

    // 解引用操作符
    T& operator*() const {return node->element;}
    T* operator->() const {return &node->element;}

    // 迭代器加法操作
    chain_iterator &operator++()  // 前加
    {
        node = node->next;
        return *this;
    }
    chain_iterator operator++(int)  // 后加
    {
        chain_iterator old = *this;
        node = node->next;
        return old;
    }
    // 相等校验
    bool operator != (const chain_iterator right) const
    {
        return node != right.node;
    }
    bool operator == (const chain_iterator right) const {
        return node == right.node;
    }

protected:
    chainNode<T>* node;

};

// 以下用链表的形式来实现线性表
template <class T>
class chain : public linearLIst<T>
{
public:
    chain(int initialCapacity = 10);
    chain(const chain<T>&);
    ~chain();

    // 抽象函数类型ADT的方法
    bool empty() const {return listSize == 0;}
    int size() const {return listSize;}
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(ostream& out) const;

    typedef chain_iterator<T> iterator;
    iterator begin() {return iterator(firstNode);}
    iterator end() {return iterator(NULL);}

protected:
    void checkIndex(int theIndex) const;
    chainNode<T>* firstNode;    // 指向链表的第一个节点的指针
    int listSize;               // 线性表的元素个数

};

//template <class T>
//class extendedChain : friend chain<T>, public extendedLinearList<T>
//{
//    void clear();
//    void push_back(const T& theElement);
//};




#endif //LEETCODE_LINEARLIST_H
