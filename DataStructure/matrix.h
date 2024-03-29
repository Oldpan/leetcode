#ifndef LEETCODE_MATRIX_H
#define LEETCODE_MATRIX_H

#include <ostream>
#include <string>
#include <iostream>
#include "linearlist.h"

class matrixIndexOutOfBounds
{
public:
    matrixIndexOutOfBounds(std::string str="matrix Index Out OfBounds"):
            message(std::move(str)){}
    matrixIndexOutOfBounds(char* theMessage)
    {message = theMessage;}
    void outputMessage() {std::cout << message << std::endl;}
private:
    std::string message;
};

class matrixSizeMismatch
{
public:
    matrixSizeMismatch(std::string str="matrix size mismatch"):
            message(std::move(str)){}
    matrixSizeMismatch(char* theMessage)
    {message = theMessage;}
    void outputMessage() {std::cout << message << std::endl;}
private:
    std::string message;
};


template <class T>
class matrix
{
    friend std::ostream &operator<<(std::ostream&, const matrix<T>&);

public:
    matrix(int theRows=0, int theColumns=0);
    matrix(const matrix<T>&);
    ~matrix() {delete [] element;}
    int row() const {return theRows;}
    int columns() const {return theColumns;}
    T& operator() (int i, int j) const;
    matrix<T>& operator=(const matrix<T>&);
    matrix<T>&operator+() const;
    matrix<T> operator+(const matrix<T>&) const;
    matrix<T> operator-() const;
    matrix<T> operator-(const matrix<T>&) const;
    matrix<T> operator*(const matrix<T>&) const;
    matrix<T>& operator+=(const T&);
    T* data() {return element;}                     // 返回原始地址
    int size() const {return theRows*theColumns;}

private:
    int theRows;
    int theColumns;
    T *element;
};


template <class T>
matrix<T>::matrix(int theRows, int theColumns)
{
    // 检查行数和列数的有效性
    if (theRows < 0 || theColumns < 0)
        throw illegalParameterValue("Row and columns must be >= 0");
    if((theRows == 0 || theColumns == 0) && (theRows != 0 || theColumns != 0))
        throw illegalParameterValue("Either both or neither rows and columns should be zero");
    // 创建矩阵
    this->theRows = theRows;
    this->theColumns = theColumns;
    element = new T [theRows * theColumns];
}

template <class T>
matrix<T>::matrix(const matrix<T>& m)
{
    // 复制构造函数
    theRows = m.theRows;
    theColumns = m.theColumns;
    element = new T [theRows * theColumns];
    copy(m.element, m.element + theRows * theColumns,
         element);
}

template <class T>
matrix<T>& matrix<T>::operator=(const matrix<T> & m)
{
    //赋值
    if(this != m) // 不能自己复制自己
    {
        delete [] element;
        theRows = m.theRows;
        theColumns = m.theColumns;
        element = new T [theRows * theColumns];
        std::copy(m.element,
                  m.element + theRows*theColumns,
                  element);
    }
    return *this;
}

template <class T>
T& matrix<T>::operator()(int i, int j) const
{
    if (i < 0 || i >= theRows || j < 0 || j >= theColumns)
        throw matrixIndexOutOfBounds();
    return element[i * theColumns + j];    // 对着了
}

template <class T>
matrix<T> matrix<T>::operator+(const matrix<T> & m) const
{
    // 返回矩阵 w = (*this) + m
    if(theRows != m.theRows || theColumns != m.theColumns)
        throw matrixSizeMismatch();

    // 生成结果矩阵
    matrix<T> w(theRows, theColumns);
    for (int i = 0; i < theRows * theColumns; i ++)
        w.element[i] = element[i] + m.element[i];
    return w;
}

template <class T>
matrix<T> matrix<T>::operator*(const matrix<T>& m) const
{
    if (theColumns != m.theRows)
        throw matrixSizeMismatch();

    matrix<T> w(theRows, m.theColumns);  // 结构矩阵
    // 定义矩阵 *this, m和w的游标且初始化以为(0,0)元素定位
    int ct = 0, cm = 0, cw = 0;
    // 对所有i和j计算w(i,j)
    for(int i = 0; i < theRows; i ++)
    {// 计算结果矩阵的第i行
        for(int j = 0; j < m.theColumns; j ++)
        {
            T sum = element[ct] * m.element[cm];     // 先把第一个数字乘起来存进去

            // 累加其余所有项
            for (int k = 1; k < theColumns; k ++)   // 然后从第二个数字开始
            {
                ct++;                               // *this中第i行的下一项
                cm += m.theColumns;                 // m中第j列的下一项
                sum += element[ct] * m.element[cm];
            }
            w.element[cw++] = sum;                  // cw 一直按顺序走就行了
            // 从第一个矩阵行的起点和第二个矩阵下一列从新开始
            ct -= theColumns - 1;
            cm = j+1;
        }
        ct = (i+1) * theColumns;
        cm = 0;
    }
    return w;
}

template <class T>
class sparseMatrix
{
public:
    void transpose(sparseMatrix<T> &b);
    void add(sparseMatrix<T> &b, sparseMatrix<T> &c);

private:
    int rows;
    int cols;
};





#endif //LEETCODE_MATRIX_H
