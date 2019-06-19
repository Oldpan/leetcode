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

protected:
    void checkIndex(int index) const;
        // 若索引无效 则抛出异常
    T* element;
    int arrayLength;        // 容量
    int listSize;           // 当前的个数

};





#endif //LEETCODE_LINEARLIST_H
