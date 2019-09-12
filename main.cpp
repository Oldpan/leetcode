#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <ctype.h>
#include <stack>
#include <map>

#include "test/test_concepts.h"

//#include "test/test_thread.h"
////#include "test/test_design_pattern.h"
//#include "utils.h"
//#include "Concepts/learnOpencv.h"

using namespace std;




// 华为笔试第三题 逻辑计算 和 加减乘除类似
// 遇到& 有三种情况 要考虑 & 的优先级
// 第一种遇到正常字符或者（，那么就把这个（）内取值，或者正常数字作为第二个数，
// 接着循环，如果遇到&或者|或者直接到末尾了表示&该计算了，就把第一个数和第二个数做个&操作，作为外层的第一个数

int dfs_normal(string &s, int start_index, int end_index);

int dfs_kh(int &index, string &s) {
    for (int i = index; i< s.size(); ++i) {
        if (s[i] == '(')
            dfs_kh(++i, s);
        else if (s[i] == ')') {
            bool res = dfs_normal(s, index, i);
            index = i;
            return res;
        }
    }
}

int dfs_normal(string &s, int start_index, int end_index) {
    int first;
    int second=-1;
    bool fei = false;
    for (int i = start_index; i < end_index; ++i) {
        if (s[i] == '(') {
            first = dfs_kh(++i, s);
        }
        else if (s[i] == '&') {
            bool fei2 = false;
            int second2;
            if (fei) {
                first = first ^ 1;
                fei = false;
            }
            int j;
            for (j = i + 1; j < end_index;++j) {  // 因为&的优先级高 所以内循环
                if (s[j] == '(') {
                    second2 = dfs_kh(++j, s);
                }
                else if (s[j] == '|'||s[j]=='&') {
                    if (fei2)
                        second2 = second2 ^ 1;
                    first = first & second2;
                    i = j - 1;
                    break;
                }
                else if (s[j] == '!')
                    fei2 = true;
                else
                    second2 = s[j];
            }
            if (j == end_index) {
                first = first&second2;
                i = j - 1;
            }
        }
        else if (s[i] == '|') {
            second = dfs_normal(s, i + 1, end_index);
            break;
        }
        else if (s[i] == '!') {
            fei = true;
        }
        else {
            first = s[i] - '0';
        }
    }
    if (fei) {
        first = first ^ 1;
    }
    if (second == -1)
        return first;
    return first|second;
}


int recur(int a, int b)
{
    if( a >= b)
    {
        if(a == b)
            return a;
        else
            return 0;
    } else{
        return recur(a+1, b-1) + a + b;
    }
}

int main()
{
//    string s;
//    cin >> s;
//    cout << dfs_normal(s, 0, s.size());

    cout << recur(8,2012);





//    test_vector();







//    test_construt_order();
//     要记住，默认都是less
//    vector<int> test = {2,4,8,3,7,5,6};
//    sort(test.begin(), test.end(), greater<>());




// 对于字符串来说也可以进行 排序 按照字符的顺序进行排序
//    string temp = "sfsfda";
//    sort(temp.begin(), temp.end());

//    test_new_operater();

//    bool vis = new bool[5*5];   // 不报错 因为vis被返回表达式了 即为真
//    int* visited = new int[5*5];
//    cout << sizeof(visited);    // 这里输出是8 因为visited是一个指针

//    test_max_heap();
//    test_singleton();
//    test_observer();
//    image_read();
//    test_throw();
//    test_shared_ptr();
//    TestSharpedPtr();


    return 0;


}