//
// Created by 郭彦宗 on 2019-07-03.
//

#include <vector>
#include <string>
#include "test_concepts.h"
#include "../DataStructure/linearlist.h"
#include "../DataStructure/matrix.h"
#include "../Concepts/smartPtr.h"

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
// https://blog.csdn.net/qq_34992845/article/details/69218843
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

void printVec(vector<int> nums)
{
    for (int i = 0; i < nums.size(); ++i)
        cout << nums[i] << " ";
    cout << endl;
}

// https://blog.csdn.net/qq_29630271/article/details/66478256
void test_max_heap()
{
    int nums_temp[] = {8, 3, 4, 8, 9, 2, 3, 4, 10};
    vector<int> nums(nums_temp, nums_temp + 9);
    cout << "make_heap之前: ";
    printVec(nums);

    cout << "(默认(less))make_heap: ";
    make_heap(nums.begin(), nums.end());
    printVec(nums);

    cout << "(less)make_heap: ";
    make_heap(nums.begin(), nums.end(), less<int> ());
    printVec(nums);

    cout << "(greater)make_heap: ";
    make_heap(nums.begin(), nums.end(), greater<int> ());
    printVec(nums);

    cout << "此时，nums为小顶堆 greater" << endl;
    cout << "push_back(3)" << endl;
    nums.push_back(3);
    cout << "默认(less)push_heap 此时push_heap失败: ";
    push_heap(nums.begin(), nums.end());
    printVec(nums);
    cout << "push_heap为greater 和make_heap一致，此时push_heap成功: ";
    push_heap(nums.begin(), nums.end(), greater<int>());
    printVec(nums);
    cout << "(greater,不然会失败)pop_heap: ";
    pop_heap(nums.begin(), nums.end(),greater<int>());  // 必须先pop_head后才能对原始的nums进行pop_back()
    printVec(nums);
    cout << "pop_back(): ";
    nums.pop_back();
    printVec(nums);

}

void test_matrix_mul()
{
    auto matrix_1 = new matrix<int>(2,3);
    auto matrix_2 = new matrix<int>(3,2);

    auto matrix1_data = matrix_1->data();
    auto matrix2_data = matrix_2->data();

    matrix1_data[0] = 1;
    matrix1_data[1] = 2;
    matrix1_data[2] = 3;
    matrix1_data[3] = 4;
    matrix1_data[4] = 5;
    matrix1_data[5] = 6;

    matrix2_data[0] = 1;
    matrix2_data[1] = 2;
    matrix2_data[2] = 2;
    matrix2_data[3] = 3;
    matrix2_data[4] = 3;
    matrix2_data[5] = 4;

    matrix<int> result = (*matrix_1) * (*matrix_2);
    for (int i = 0; i < result.size(); i ++)
        cout << result.data()[i];

}

void test_string()
{
    string s1;
    string s2(s1);
    string s3("Value");   // 执行直接初始化函数
    string s4 = "Value";
    string s5(5,'c');     // 类vector
    if(s5.empty() || s5.size() < 5)
        s5 += s4;

    s5.erase(s5.end()-1);  // 去除s5最后一个字符

}

void test_new_and_malloc()
{
    char* temp1 = new char[100];
    // 要注意malloc返回的是 void* 类型
    char* temp2 = (char*)malloc(sizeof(char) * 100);

    delete [] temp1;
    free(temp2);
}

void TestSharpedPtr()
{
    SharpedPtr<int> ap1(new int(10));
    SharpedPtr<int> ap2(new int(20));
    SharpedPtr<int> ap3(ap1);
    SharpedPtr<int> ap4;
    ap4 = ap1;
    *ap1 = 1;
    *ap2 = 2;
    *ap3 = 3;
    *ap4 = 4;
}

void test_array_name()
{
    int text[5] = {1,2,3,4,5};
    cout << *text << endl;                  // 输出1
    cout << *(text+1) << endl;              // 输出2
    cout << text << endl;                   // 0x7ffee4ffba30
    cout << text+1 << endl;                 // 0x7ffee4ffba34  一个int是4位
    cout << &text+1 << endl;                // 0x7ffee4ffba44  16进制 0x14 --> 十进制的4*5=20
}