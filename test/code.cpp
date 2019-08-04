// 这里存放所有做过题的"模板"

#include <iostream>
#include <vector>

using namespace std;


// 全排列 123 132 213 232 312 321
// 但是这个全排列不是字典序排列
void backtrack(vector<int> &nums,vector<vector<int>> &res,int i){
    if(i==nums.size())
        res.push_back(nums);

    for(int j=i;j<nums.size();j++){
        swap(nums[i],nums[j]);
        backtrack(nums,res,i+1);
        swap(nums[i],nums[j]);
    }
}

// 字典序的全排列 与上面那个相比 是有顺序的
void backtrack_order(vector<int> &nums,vector<vector<int>> &res,int i){

    auto length = nums.size();

    while(true)
    {
        int j,k;
        res.push_back(nums);

        for (j = length - 2; j >= 0 && nums[j] > nums[j + 1]; j--);  //注意此处 j >= 0 判断条件在前

        if (j < 0)
            break;

        for (k = length - 1; k > j&&nums[k] < nums[j]; k--);

        swap(nums[k], nums[j]);

        for (int l = j + 1, r = length - 1; l < r; l++, r--)
            swap(nums[l], nums[r]);

        break;
    }
}




// 不定长数组输入 回车结束
//while(cin>>num)
//{
//    vec.push_back(num);
//    if (getchar()=='\n')
//        break;
//}




//    拼多多笔试最后一题
//    int res = 0;
//    int N;
//    cin >> N;
//
//    vector<pair<int, int>>cube(N, {0,0});
//
//    int temp;
//    for (int i = 0; i != N; ++i) {
//        cin >> temp;
//        cube[i].first = temp;
//    }
//    for (int i = 0; i != N; ++i) {
//        cin >> temp;
//        cube[i].second = temp;
//    }
//
//    sort(cube.begin(), cube.end());
//    vector<vector<int>>dp(N, vector<int>(N, 100000000));
//    dp[0][0] = cube.front().second;
//
//    // dp中第一维为第i块 第二维为第高度 然后dp[i][j]表示当前 使用第i块的时候j高度的时候 最小重量
//    // 就是遍历到第i块时叠j+1块高度最小重量为 遍历到i-1块时，总重量比第i块的7倍小的重量dp[i - 1][j]+第i块重量中的最小值
//    // 这个从上开始往下放
//    for (int i = 1; i != N; ++i)
//    {
//        for (int j = 0; j <= i; ++j) {
//            if (dp[i - 1][j] <= cube[i].second * 7) {
//                dp[i][j + 1] = min(dp[i][j + 1], dp[i - 1][j] + cube[i].second);
//                res = max(res, j + 1);
//            }
//            else {
//                dp[i][j] = min(dp[i][j], dp[i - 1][j]);
//            }
//        }
//    }
//
//    cout << res + 1;



// 拼多多第二题 dfs题

//bool dfs(int n, vector<bool>&visited, vector<vector<int>>&find_by_first, vector<pair<char, char>>&s_vec, int cur_node) {
//    if (n == s_vec.size()&& s_vec[cur_node].second==s_vec[0].first)
//        return true;
//    auto &next_node = find_by_first[s_vec[cur_node].second-'A'];
//    for (int i = 0; i != next_node.size(); ++i) {
//        if (!visited[next_node[i]]) {
//            visited[next_node[i]] = true;
//            if (dfs(n + 1, visited, find_by_first, s_vec, next_node[i]))
//                return true;
//            visited[next_node[i]] = false;
//        }
//    }
//    return false;
//}

//    string s;
//    getline(cin, s);
//    vector<pair<char,char>>s_vec;
//    stringstream stringin(s);
//    string temp;
//    while (stringin >> temp) {
//        s_vec.push_back({temp.front(),temp.back()});
//    }
//    vector<vector<int>>find_by_first(26,vector<int>());
//    vector<bool>visited(find_by_first.size(), false);
//    for (int i = 0; i != s_vec.size(); ++i) {
//        find_by_first[s_vec[i].first - 'A'].push_back(i);
//    }
//    visited[0] = true;
//    if (dfs(1, visited, find_by_first, s_vec, 0))
//        cout << "true";
//    else
//        cout << "false";
//    return 0;
