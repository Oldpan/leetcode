#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <ctype.h>
#include <stack>

#include "test/test_concepts.h"
//#include "test/test_thread.h"
////#include "test/test_design_pattern.h"
#include "utils.h"
//#include "Concepts/learnOpencv.h"

using namespace std;


//vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
//
//    priority_queue<int, vector<int>> min_heap;
//    vector<int> result;
//    for(int i = 0; i < input.size(); i ++)
//    {
//        if(min_heap.size() < k)
//        {
//            min_heap.push(input[i]);
//            continue;
//        }
//        if(min_heap.top() > input[i])
//        {
//            min_heap.pop();
//            min_heap.push(input[i]);
//        }
//    }
//    while(!min_heap.empty()){
//        result.push_back(min_heap.top());
//        min_heap.pop();
//    }
//
//    return result;
//}


struct p
{
    int x;
    int y;
};


int pre[200]; //存放第i个元素的父节点

int unionsearch(int root) //查找根结点
{
    int son, tmp;
    son = root;
    while(root != pre[root])  //寻找根结点
        root = pre[root];
    while(son != root)   //路径压缩
    {
        tmp = pre[son];
        pre[son] = root;
        son = tmp;
    }
    return root;
}

void join(int root1, int root2)    // 判断是否连通，不连通就合并
{
    int x, y;
    x = unionsearch(root1);
    y = unionsearch(root2);
    if(x != y)                     // 如果不连通，就把它们所在的连通分支合并
        pre[x] = y;
}

int findCircleNum(vector<vector<int>>& M)
{
    auto row = M.size();
    auto col = M[0].size();
    int res = 0;

    for(int i = 0; i < 200; i ++)
        pre[i] = i;

    for(int i = 0; i < row; i++)
        for(int j = i+1; j < col; j ++)
        {
            if(M[i][j] == 1)
                join(i,j);
        }

    for(int i = 0; i < row; i ++)
    {
        if(i == pre[i])
            res ++;
    }

    return res;
}

int main()
{
    vector<vector<int>> test = {{1,0,0,1},{0,1,1,0},{0,1,1,1},{1,0,1,1}};
    int res = findCircleNum(test);















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





    test_construt_order();
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