#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <stack>
#include <map>
#include <cstring>
#include <unistd.h>

#include "test/test_concepts.h"
#include "test/test_thread.h"
//#include "test/test_design_pattern.h"
#include "utils.h"
//#include "Concepts/learnOpencv.h"
//#include "test/c_polymorphism.h"

using namespace std;




int main()
{











//    string test;
//    getline(cin, test);
//    vector<pair<char,int>> res;
//    map<char, pair<int, int>> char2index2count;
//
//    int index = 0;
//    for(int i = 0; i < test.size(); i ++)
//    {
//        if(char2index2count.count(test[i]))
//            char2index2count[test[i]].second ++;
//        else
//        {
//            pair<int, int> temp = {index, 1};
//            char2index2count[test[i]] = temp;
//        }
//        index ++;
//    }
//
//    for(auto& tt :char2index2count)
//    {
//        if(tt.second.second <= 5 && tt.second.second >= 3)
//        {
//            res.push_back({tt.first, tt.second.first});
//        }
//    }
//    if(res.empty())
//        cout << "no";
//
//    sort(res.begin(), res.end(), [](const pair<char,int>& a, pair<char,int>& b){
//        return a.first > b.first;
//    });
//
//    for(auto& temp:res)
//    {
//        cout << temp.first;
//    }








//    int nums = 10;
//    int len = 3;
//    float sub_value = float(nums) / len;
//    if(int(sub_value) != sub_value)
//        cout << "!!!";

//    test_vector();

//    int n,m;
//    cin >> n;
//    cin >> m;
//    vector<int> first;
//    vector<int> second;
//    vector<int> index_num_1(m,0);
//    vector<int> index_num_2(m,0);
//    int temp;
//    for(int i = 0; i < n; i ++)
//    {
//        cin >> temp;
//        first.push_back(temp);
//        index_num_1[temp] ++;
//    }
//    for(int i = 0; i < n; i ++)
//    {
//        cin >> temp;
//        second.push_back(temp);
//        index_num_2[temp] ++;
//    }
//
//    vector<int> res(n, 0);
//    int count = 0;
//
//    for(int sub_num = 0; sub_num <= m; sub_num ++)
//    {
//        for(int i = m-sub_num-1; i >= 0; i --)
//        {
//
//            if(index_num_1[i] > 0 && index_num_2[m-1-i-sub_num] > 0)
//            {
//                res[count++] = m-1;
//                index_num_1[i] --;
//                index_num_2[m-1-i-sub_num] --;
//            }
//
//            for(int tt = m-1; tt >=0; tt --)
//                for(int j = m-1; j >= 0; j--)
//                {
//                    if(index_num_1[tt] > 0 && index_num_2[j] > 0 && (tt+j) % m == i)
//                    {
//                        res[count++] = m-1;
//                        index_num_1[tt] --;
//                        index_num_2[j] --;
//                    }
//                }
//        }
//
//    }
//
//    for(int i = 0; i < n; i ++)
//        cout << res[i] << ' ' ;
//    return 0;





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