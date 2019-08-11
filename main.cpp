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
//#include "utils.h"
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


//int test(vector<vector<char>>& maze) {
//    if(maze.empty())
//        return 0;
//    int row = maze.size();
//    int col = maze[0].size();
//    int num_of_1 = 0;
//
//    for (int r = 0; r < row; ++r)
//        for (int c = 0; c < row; ++c)
//        {
//            if (maze[r][c] == '1')
//                ++ num_of_1;
//
//                maze[r][c] = '0';
//
//                queue<pair<int, int>> my_queue;
//
//                my_queue.push({r, c});
//
//                while (!my_queue.empty()) {
//
//                    auto rc = my_queue.front();
//                    my_queue.pop();
//                    int row = rc.first, col = rc.second;
//                    if (row - 1 >= 0 && maze[row - 1][col] == '1') {
//                        my_queue.push({row - 1, col});
//                        maze[row - 1][col] = '0';
//                    }
//                    if (row + 1 < row && maze[row + 1][col] == '1') {
//                        my_queue.push({row + 1, col});
//                        maze[row + 1][col] = '0';
//                    }
//                    if (col - 1 >= 0 && maze[row][col - 1] == '1') {
//                        my_queue.push({row, col - 1});
//                        maze[row][col - 1] = '0';
//                    }
//                    if (col + 1 < col && maze[row][col + 1] == '1') {
//                        my_queue.push({row, col + 1});
//                        maze[row][col + 1] = '0';
//                    }
//                }
//
//            }
//        }
//}
//

//int lengthOfLIS(vector<int>& nums) {
//
//    if(nums.empty())
//        return 0;
//
//    auto length = nums.size();
//    int res = 0;
//    vector<vector<int>> dp(length+1, vector<int>(length+1,10000000));
//    dp[0][1] = nums[0];
//    for(int i = 1; i < length; i ++)
//        for(int j = 2; j <= i+1; j ++)
//        {
//            if(dp[i-1][j-1] < nums[i])
//            {
//                dp[i][j] = nums[i];
//                res = max(res, j);
//            }
//            else
//                dp[i][j-1] = nums[i];
//        }
//    return res;
//}

//
//int min_sub(int num1, int num2)
//{
//    int x, y;
//    x = num1;
//    y = num2;
//    while(num1 != num2) {           //循环条件为两数不相等
//        if(num1 > num2)             //如果第一个数大于第二个数
//            num1 = num1 - num2;     //两数相减
//        else
//            num2 = num2 - num1;
//    }
//
//    return x*y/num1;
//}

int main()
{








    return 0;


//    test_construt_order();
    // 要记住，默认都是less
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