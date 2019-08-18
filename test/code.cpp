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

// 字典序的全排列 与上面那个相比 是有顺序的 这个其实就是不停地进行下一个排序(类似于leetcode上的)
void backtrack_order(vector<int> &nums,vector<vector<int>> &res,int i){

    auto length = nums.size();

    while(true)
    {
        int j,k;
        res.push_back(nums);

        for (j = length - 2; j >= 0 && nums[j] > nums[j + 1]; j--);  //注意此处 j >= 0 判断条件在前

        if (j < 0)
            break;

        for (k = length - 1; k > j && nums[k] < nums[j]; k--);

        swap(nums[k], nums[j]);

        for (int l = j + 1, r = length - 1; l < r; l++, r--)
            swap(nums[l], nums[r]);

        break;
    }
}




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
// 这样调用
//string s;
//cin >> s;
//cout << dfs_normal(s, 0, s.size());



// 华为第一道 简单的差集 不过要记住字符串的操作方式
//    vector<int> all_chars(52,0);
//    vector<int> have_chars(52,0);
//    vector<int> order;
//
//    string s;
//    getline(cin, s);
//    bool flag = true;
//    char temp_char = 0;
//
//    for(int i = 0; i < s.size(); i ++)
//    {
//        auto item = s[i];
//        if(flag)
//        {
//            if(isalpha(item))     // 判断该字符是不是字母
//                temp_char = item;
//
//            if(isdigit(item))   // 判断该字符是不是数字
//            {
//                if(isupper(temp_char))
//                {
//                    all_chars[temp_char-'A' + 26] = item - '0';
//                    order.push_back(temp_char-'A' + 26);
//                }
//                else
//                {
//                    all_chars[temp_char-'a'] = item - '0';
//                    order.push_back(temp_char-'a');
//                }
//            }
//            if(item == '@')
//                flag = false;
//
//        } else
//        {
//            if(isalpha(item))
//                temp_char = item;
//
//            if(isdigit(item))
//            {
//                if(isupper(temp_char))
//                    have_chars[temp_char-'A' + 26] = item - '0';
//                else
//                    have_chars[temp_char-'a'] = item - '0';
//            }
//        }
//    }
//
//    for(int i = 0; i < 52; i ++)
//    {
//        all_chars[i] = all_chars[i] - have_chars[i];
//    }
//
//
//    string out = "";
//    string temp = ":";
//
//    for(int i = 0; i < order.size(); i ++)
//    {
//        int count = order[i];
//        if(count < 26 && all_chars[count] != 0)
//        {
//            out += char('a' + count) + temp + to_string(all_chars[count]);
//            out += char(',');
//
//        }
//        if(count >= 26 && all_chars[count] != 0)
//        {
//
//            out += char('A' + count-26) + temp + to_string(all_chars[count]);
//            out += char(',');
//
//        }
//    }
//
//    out.erase(out.end()-1);
//    cout << out;



// 不定长数组输入 回车结束
//while(cin>>num)
//{
//    vec.push_back(num);
//    if (getchar()=='\n')
//        break;
//}

//    拼多多笔试最后一题 搭积木的问题 动态规划
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
//        for (int j = 0; j <= i; ++j) {    // j高度从0 开始 所以最后结果要+1
//            if (dp[i - 1][j] <= cube[i].second * 7) {
//                dp[i][j + 1] = min(dp[i][j + 1], dp[i - 1][j] + cube[i].second);
//                res = max(res, j + 1);
//            }
//            else {
//                dp[i][j] = min(dp[i][j], dp[i - 1][j]);  // 如果放不下 是不是有把当前拿下来的可能性更好
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


// 网易互娱第一题 算1的个数
//typedef unsigned long long ull;
//
//int batch;
//cin >> batch;
//while(batch --)
//{
//int n;
//vector<ull> test_list;
//int temp;
//cin >> n;
//while(n--)
//{
//cin>>temp;
//test_list.push_back(temp);
//}
//
//unordered_map<int, int> num2count;
//auto len = test_list.size();
//for(int i = 0; i < len; i ++)
//{
//ull num = test_list[i];
//ull tool = 0x1;
//int count = 0;
//
//while(tool)
//{
//if(num & tool)
//count ++;
//tool = tool << 1;
//}
//
//if(!num2count.count(count))
//num2count.insert({count, 1});
//num2count[count] ++;
//
//}
//
//auto res = num2count.size();
//cout << res;
//
//}


// 网易互娱第二题 游泳池问题 做题思想学一学
//int batch;
//cin >> batch;
//while(batch --)
//{
//int m;
//cin >> m;
//int t;
//cin >> t;
//int m1;
//cin >> m1;
//int t1;
//cin >> t1;
//int m2;
//cin >> m2;
//int t2;
//cin >> t2;
//
//int curr_m = 0;
//
//for(int i = 0; i < t; i ++)
//{
//if(i % (2*t1) < t1 && i % (2*t2) < t2)
//curr_m = min(m, max(0, curr_m + m1 - m2));
//if(i % (2*t1) < t1 && i % (2*t2) >= t2)
//curr_m = min(m, curr_m + m1);
//if(i % (2*t1) >= t1 && i % (2*t2) < t2)
//curr_m = max(0, curr_m - m2);
//}
//
//cout << curr_m << endl;
//
//}


// 网易互娱第三题 不是很难 双指针即可
//int T;
//cin >> T;
//while (T > 0) {
//T--;
//string s;
//cin >> s;
//int res=0;
//int start = 0;
//int end = 0;
//int count = 0;
//
//if (s.empty()) {
//cout << res << endl;
//break;
//}
//while (end < s.size()) {
//if (s[end] != 'N') {
//count++;
//}
//end++;
//if (count >= 3) {
//while (start < end) {
//if (s[start] != 'N') {
//count--;
//}
//start++;
//if (count <= 2)
//break;
//}
//}
//res = max(res, end - start);
//}
//cout << res << endl;
//}