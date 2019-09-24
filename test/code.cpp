// 这里存放所有做过题的"模板"

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>

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

// 字符串的字典排列 不知道为什么在牛客上会超时
vector<string> Permutation(string str) {

    vector<string> res;
    auto len = str.size();

    while(true)
    {
        int j,k;
        res.push_back(str);
        for(j = len - 2; j >= 0 && str[j] > str[j+1]; j --);
        if(j < 0)
            break;
        for(k = len - 1; k > j && str[k] < str[j]; k --);
        swap(str[k], str[j]);

        for(int l = j + 1, r = len - 1; l < r; l ++, r --)
            swap(str[l], str[r]);
    }
    return res;
}

// 最长子数组的最大和一维dp即可  leetcode 53　动态规划
int FindGreatestSumOfSubArray(vector<int> array)
{
    auto len = array.size();
    if(len < 2)
        return array[0];

    vector<int> dp(len, 0);
    dp[0] = array[0];
    int max_len = dp[0];
    for(int i = 1; i < len; i++)
    {
        dp[i] = max(array[i], array[i] + dp[i-1]);
        max_len = max(max_len, dp[i]);
    }

    return max_len;
}


//416. 分割等和子　转化为背包问题做 动态规划
bool canPartition(vector<int>& nums)
{
    int sum = 0;
    auto len = nums.size();
    for(int i = 0; i < nums.size(); i ++)
        sum += nums[i];
    if(sum % 2 != 0 || len < 2)
        return false;
    int target = sum/2;

    vector<vector<int>> dp(len+1, vector<int>(target+1, 0));
    for(int i = 1; i <= len; i ++)
        for(int j = 1; j <= target; j ++)
        {
            if(j >= nums[i-1])
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-nums[i-1]] + nums[i-1]);
            else
                dp[i][j] = dp[i-1][j];
        }
    // 如果是求最接近的则是　return sum - 2*dp[len][target];
    return dp[len][target] == target;
}

// 美团第一题比较函数 比较两个字符串　学习字符串比较规则
// 规则 从第一个字符开始比较 在后面的字母比在前面的字母大
// 如果两个字符串的前缀一样 那么短的在前面
bool cmp(string& s1, string& s2)
{
    if(s1.empty())
        return true;
    if(s2.empty())
        return false;
    int min_len = min(s1.size(), s2.size());
    for(int i = 0; i < min_len; i ++)
    {
        if(s1[i] > s2[i])
            return true;
        else
            if(s1[i] < s2[i])
                return false;
    }
    return s1.size() <= s2.size();
}

// leetcode 164 给定一个无序的数组，找出数组在排序之后，相邻元素之间最大的差值。
// 这个题是陌陌的现场笔试第一题
// 设置n+1个桶是为了保证间距最大的两个数被分到不同的桶中
// 因为最大间距 x >= (max_val - min_val) / (n-1)
// 而使用n+1个桶每个桶中数的差值最大为 (max_val - min_val) / n 因此一个桶不可能同时存放间距最大的两个数
typedef pair<int, int> min_and_max;

int bucketNum(vector<int>& a, int i, int min, int max, int len)
{
    return long(a[i] - min) * len / (max - min);
}

int maximumGap(vector<int>& nums) {

    auto len = nums.size();
    if(len < 2)
        return 0;
    int max_value = 0;

    for(auto& num:nums)
        max_value = max(max_value,num);
    int min_value = INT32_MAX;
    for(auto& num:nums)
        min_value = min(min_value, num);

    vector<int> bucket_list(len + 1, 0);
    vector<min_and_max> minmax(len + 1, min_and_max(0,0)); // 记录当前桶最小最大值
    vector<bool> has_num(len + 1, false);  // 记录当前是否有数

    for(int i = 0; i < len; i ++)
    {
        int bucketId = bucketNum(nums, i, min_value, max_value, len);
        minmax[bucketId].first = has_num[bucketId] ? min(minmax[bucketId].first, nums[i]) : nums[i];
        minmax[bucketId].second = has_num[bucketId] ? max(minmax[bucketId].second, nums[i]) : nums[i];
        has_num[bucketId] = true;
    }

    int resMax = 0;  // 记录最大差值
    int lastMax = 0; // 记录当前空桶的上一个桶的最大值

    int i = 0;
    while (i < len + 1){
        //遍历桶，找到一个空桶
        while (i < len + 1 && has_num[i])
            i ++;
        if(i == len + 1)
            break;
        lastMax = minmax[i-1].second;
        //继续遍历桶，找到下一个非空桶
        while(i < len + 1 && !has_num[i])
            i ++;
        if(i == len + 1)
            break;
        resMax = max(resMax, minmax[i].first - lastMax);
    }
    return resMax;
}


//函数功能: 计算Catalan的第n项
//函数参数: n为项数
//返回值:  第n个Catalan数

int Catalan(int n)
{
    if(n<=1) return 1;
    int *h = new int [n+1]; //保存临时结果
    h[0] = h[1] = 1;        //h(0)和h(1)
    for(int i=2;i<=n;++i)    //依次计算h(2),h(3)...h(n)
    {
        h[i] = 0;
        for(int j = 0; j < i; j++) //根据递归式计算 h(i)= h(0)*h(i-1)+h(1)*h(i-2) + ... + h(i-1)h(0)
            h[i] += (h[j] * h[i-1-j]);
    }
    int result = h[n]; //保存结果
    delete [] h;       //注意释放空间
    return result;
}


struct ListNode{
    struct ListNode* next;
    int val;
    ListNode(int x):val(x), next(nullptr){}
};

// 简单的翻转链表 inplace版的
ListNode* ReverseList(ListNode* pHead)
{
    ListNode* pCurr=pHead;
    ListNode* pPre=nullptr;
    ListNode* pNext=nullptr;
    ListNode* pRes=nullptr;

    while(pCurr!=nullptr)
    {
        pNext=pCurr->next;
        if(pNext == nullptr){
            pRes=pNext;
        }
        pCurr->next=pPre;
        pPre=pCurr;
        pCurr=pNext;
    }
    return pPre;
}


// leetcode　朋友圈 并查集
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


// 01 连通域矩阵 求连通的1的个数 使用BFS而不是DFS(DFS容易栈溢出)
int maze_01(vector<vector<char>>& maze)
{
    if(maze.empty())
        return 0;
    int row = maze.size();
    int col = maze[0].size();
    int num_of_1 = 0;

    for (int r = 0; r < row; ++r)
        for (int c = 0; c < col; ++c)
        {
            if (maze[r][c] == '1')
            {
                ++ num_of_1;

                maze[r][c] = '0';

                queue<pair<int, int>> my_queue;

                my_queue.push({r, c});

                while (!my_queue.empty()) {

                    auto rc = my_queue.front();
                    my_queue.pop();
                    int row = rc.first, col = rc.second;
                    if (row - 1 >= 0 && maze[row - 1][col] == '1') {
                        my_queue.push({row - 1, col});
                        maze[row - 1][col] = '0';
                    }
                    if (row + 1 < row && maze[row + 1][col] == '1') {
                        my_queue.push({row + 1, col});
                        maze[row + 1][col] = '0';
                    }
                    if (col - 1 >= 0 && maze[row][col - 1] == '1') {
                        my_queue.push({row, col - 1});
                        maze[row][col - 1] = '0';
                    }
                    if (col + 1 < col && maze[row][col + 1] == '1') {
                        my_queue.push({row, col + 1});
                        maze[row][col + 1] = '0';
                    }
                }
            }
        }
    return num_of_1;
}

// 最小公倍数
int min_sub(int num1, int num2)
{
    int x, y;
    x = num1;
    y = num2;
    while(num1 != num2) {           //循环条件为两数不相等
        if(num1 > num2)             //如果第一个数大于第二个数
            num1 = num1 - num2;     //两数相减
        else
            num2 = num2 - num1;
    }

    return x*y/num1;
}

// 计算1-n中有多少数字包含１
int count_how_many_1(int n)
{
    int count = 0;      //统计变量
    int factor = 1;     //分解因子
    int lower = 0;      //当前处理位的所有低位
    int higher = 0;     //当前处理位的所有高位
    int curr =0;        //当前处理位

    while(n/factor != 0)
    {
        lower = n - n/factor*factor;        //求得低位
        curr = (n/factor)%10;               //求当前位
        higher = n/(factor*10);             //求高位

        switch(curr)
        {
            case 0:
                count += higher * factor;
                break;
            case 1:
                count += higher * factor + lower + 1;
                break;
            default:
                count += (higher+1)*factor;
        }

        factor *= 10;
    }

    return count;
}


// 按距离k间隔重排字符串 leetcode-358 加密题　bigo面试题
// 先用 HashMap 或者Array 对字符串里的字符按出现次数进行统计，按次数由高到低进行排序。
// 还是先统计字符出现的次数，按出现次数排列组成最大堆。
// 然后每次从堆中去取topk 的字符排入结果，相应的字符数减1，如此循环，直到所有字符排完。

string rearrangeString(string s, int k)
{
    if (k == 0) {
        return s;
    }
    int len = s.size();
    string result;
    map<char, int> hash;                                // map from char to its appearance time
    for(auto ch: s) {
        ++hash[ch];
    }
    priority_queue<pair<int, char>> que;                // using priority queue to pack the most char first
    for(auto val: hash) {
        que.push(make_pair(val.second, val.first));
    }
    while(!que.empty()) {
        vector<pair<int, int>> vec;
        int cnt = min(k, len);
        for(int i = 0; i < cnt; ++i, --len) {           // try to pack the min(k, len) characters sequentially
            if(que.empty()) {                           // not enough distinct charachters, so return false
                return "";
            }
            auto val = que.top();
            que.pop();
            result += val.second;
            if(--val.first > 0) {                       // collect the remaining characters
                vec.push_back(val);
            }
        }
        for(auto val: vec) {
            que.push(val);
        }
    }
    return result;
}


// leetcode 621　任务调度
// 先用哈希表或者数组对任务出现的次数进行统计，找出任务出现次数的最大值max_count(有可能是多个)，
// 然后把这个任务(或者任务对)之间按n个间隔进行分隔排列，然后把其它任务插到这些间隔里面。
// 由于其它任务出现的次数少于max_count所以肯定能放下，如有空位就是需要空闲(idle)。
// 最后，还要注意的是，如果空位都插满之后还有任务，那就随便在这些间隔里面插入就可以，
// 因为间隔长度肯定会大于n，在这种情况下就是任务的总数是最小所需时间。

int leastInterval(vector<char>& tasks, int n)
{
    int mx = 0;       // 最长任务出现的次数
    int mxCnt = 0;    // 最长任务出现的个数
    vector<int> cnt(26, 0);
    for (char task : tasks) {
        ++cnt[task - 'A'];
        if (mx == cnt[task - 'A']) {
            ++mxCnt;
        } else if (mx < cnt[task - 'A']) {
            mx = cnt[task - 'A'];
            mxCnt = 1;
        }
    }
    int partCnt = mx - 1;            // 最多个数任务的间隔
    int partLen = n - (mxCnt - 1);   // 在这些间隔中　插其他同样出现次数的任务　剩下的　如果剩下-1则都插满了　还可以插
    int emptySlots = partCnt * partLen;
    int taskLeft = tasks.size() - mx * mxCnt;
    int idles = max(0, emptySlots - taskLeft);
    return tasks.size() + idles;
}


// 拼多多第二批笔试　第二道算法题 直接用dfs做就可以了

void dfs(vector<char>& res_one, vector<string>& res, string s1, string s2, string& s1_new, int N)
{
    if (s1_new == s2 && s1.size() == 0 && res_one.size() == N)
    {
        string ans;
        for (int i = 0; i < res_one.size(); i  )
        {
            ans  = res_one[i];
        }
        res.push_back(ans);
        return;
    }

    while (s1.size())
    {
        char tmp = s1[0];         // 取出最左边的
        s1 = s1.substr(1);   // 然后这个是剩下的
        // 学学这种写的方式　先push进去　然后pop出来
        res_one.push_back('d');
        dfs(res_one, res, s1, s2, s1_new, N);
        res_one.pop_back();

        res_one.push_back('l');
        s1_new = tmp + s1_new;   // 将上一个牌的最左边放到新的最左边
        dfs(res_one, res, s1, s2, s1_new, N);
        s1_new = s1_new.substr(1);
        res_one.pop_back();

        res_one.push_back('r');
        s1_new = s1_new + tmp; // 将上一个牌的最左边放到新的最右边
        dfs(res_one, res, s1, s2, s1_new, N);
        s1_new = s1_new.substr(0, s1_new.length() - 1);
        res_one.pop_back();

    }

    return;
}
int fake_main()
{
    int T;
    cin >> T;

    string s1;
    string s2;
    string s1_new;

    while (T--)
    {
        cin >> s1;
        cin >> s2;
        vector<char> res_one;
        vector<string> res;

        dfs(res_one, res, s1, s2, s1_new, s1.length());

        sort(res.begin(), res.end());

        cout << "{" << endl;

        for (int i = 0; i < res.size(); i  )
        {
            for (int j = 0; j < s1.length(); j  )
            {
                cout << res[i][j] << " ";
            }
            cout << "\n";
        }

        cout << "}" << endl;
    }

    return 0;
}



// 84　柱状图中的最大矩形
// https://blog.csdn.net/Prasnip_/article/details/83690038
int largestRectangleArea(vector<int>& heights)
{
    heights.push_back(0);     // 在最后面放一个0以计算将所有数据导出来的结果
    auto len = heights.size();
    stack<int> my_stack;
    long res = 0;
    long width;
    long min_height;
    stack<int> weight;         // 这个存储宽度的栈与my_stack同步操作


    for(int i = 0; i < len; i ++)
    {

        if(my_stack.empty())
        {
            my_stack.push(heights[i]);
            weight.push(1);        // 正常的都是１
            continue;
        }
        if(my_stack.top() > heights[i])
        {
            width = 0;
            min_height = INT32_MAX;
            while (!my_stack.empty() && my_stack.top() >= heights[i])
            {
                long temp = my_stack.top();
                long temp_height = weight.top();

                width += temp_height;
                min_height = min(min_height, temp);
                res = max(res, width*min_height);

                my_stack.pop();
                weight.pop();
            }
        }

        my_stack.push(heights[i]);
        weight.push(1+width);  // 因为把高的都去掉了　但是要保留他们的宽度
        width = 0;
    }

    return res;
}



// 拼多多第三题　多个筛子最大得分的期望
#define for0(a, n) for (int (a) = 0; (a) < (n); (a)  )
#define for1(a, n) for (int (a) = 1; (a) <= (n); (a)  )
#define mem(a,x)  memset(a,x,sizeof a)

const int maxN=50;
const int maxK=50;

double P[maxK+5];
int cnt[maxK+5];
int sum[maxK+5];
int n,maxk;

double solve(int x)
{
    int num_ge=sum[maxk]-sum[x-1];
    if(!num_ge) return 0;

    double p=1;

    for(int i=x;i<=maxk;i  ) if(cnt[i])
        {
            p*= pow(1.0*x/i, cnt[i]);
        }

    double p2=1;
    for(int i=x;i<=maxk;i  ) if(cnt[i])
        {
            p2*= pow(1.0*(x-1)/i,cnt[i] );
        }

    return  p-p2;

}
int fake_main2()
{
    std::ios::sync_with_stdio(false);
    int x;
    while(cin>>n)
    {
        mem(cnt,0);maxk=0;
        for1(i,n)
        {
            cin>>x;maxk=max(maxk,x);cnt[x];
        }
        sum[0]=0;
        for1(i,maxk)
        sum[i]=sum[i-1] + cnt[i];

        for1(i,maxk)  P[i]=solve(i);

        double ans=0; for1(i,maxk)  ans =P[i]*i;
        printf("%.2f\n",ans);
    }

    return 0;
}



// leetcode 单调递增数
// 这道题用贪心　738
int monotoneIncreasingDigits(int N)
{
    vector<int> nums;
    long interval = 1000000000;
    bool flag = false;
    long resn = N;
    while(interval)
    {
        auto bit = N/interval;
        if(bit == 0 && !flag)
        {
            interval /= 10;
            continue;
        }
        nums.push_back(bit);
        flag = true;
        if(interval == 1)
            break;
        N %= interval;
        interval /= 10;
    }
    int max_index = 0;
    long max_value = 0;
    bool is_result = true;
    for(int i = 0; i < nums.size()-1; i ++)
    {
        if(nums[i] <= nums[i+1])
        {
            if(nums[i] > max_value) {
                max_index = i;
                max_value = nums[i];
            }
        } else
        {
            if(nums[i] > max_value) {
                max_index = i;
                max_value = nums[i];
            }
            is_result = false;
            break;
        }
    }

    if(is_result)
        return resn;

    nums[max_index] -= 1;
    for(int i = max_index + 1; i < nums.size(); i ++)
    {
        nums[i] = 9;
    }

    long res = 0;
    long mul = pow(10, nums.size()-1);
    for(int i = 0; i < nums.size(); i ++)
    {
        res += nums[i] * mul;
        mul /= 10;
    }
    return res;
};

// 单词拆分 leetcode 139　动态规划 dp
bool wordBreak(string s, vector<string>& wordDict) {

    if(s.empty() || wordDict.empty())
        return false;

    // dp[i]表示字符串的前i个字符能否拆分成wordDict
    vector<bool> dp(s.size() + 1, false);
    unordered_set<string> m(wordDict.begin(), wordDict.end());
    dp[0] = true;
    for(int i = 1; i <= s.size(); i ++)
    {
        for(int j = 0; j < i; j ++)
        {
            if(dp[j] && m.find(s.substr(j, i-j)) != m.end())
            {
                dp[i] = true;
                break;
            }
        }
    }
    return dp[s.size()];

}


// 单词搜索 leetcode 79
class Solution_79
{
public:
    bool exist(vector<vector<char>> &board, string word)
    {
        if (board.size() == 0)
            return false;
        h = board.size();
        w = board[0].size();
        for (int i = 0; i < w; i++)
            for (int j = 0; j < h; j++)
                if (search(board, word, 0, i, j))
                    return true;
        return false;
    }

    bool search(vector<vector<char>> &board,
                const string &word, int d, int x, int y)
    {
        if (x < 0 || x == w || y < 0 || y == h || word[d] != board[y][x])
            return false;

        if (d == word.length() - 1)
            return true;

        char cur = board[y][x];
        board[y][x] = 0;  // 注意这里必须设置为0 代表没有已经走过
        bool found = search(board, word, d + 1, x + 1, y)
                     || search(board, word, d + 1, x - 1, y)
                     || search(board, word, d + 1, x, y + 1)
                     || search(board, word, d + 1, x, y - 1);
        board[y][x] = cur;  // 但是回来的时候记得复原
        return found;
    }

private:
    int w;
    int h;

};

// 圆圈中最后剩下的数字 找规律求解出来 牛客原题
int lastRemaining(int n, int m)
{
    if(n < 1 || m < 1)
        return -1;

    int last = 0;
    for(int i = 2; i <= n; i ++)
        last = (last + m) % i;
    return last;
}



//　假设f(m,s)表示投第m个骰子时，点数之和s出现的次数,投第m个骰子时的点数之和只与投第m-1个骰子时有关。
//递归方程：f(m,s)=f(m-1,s-1)+f(m-1,s-2)+f(m-1,s-3)+f(m-1,s-4)+f(m-1,s-5)+f(m-1,s-6)，
// 表示本轮点数和为s出现次数等于上一轮点数和为s-1，s-2，s-3，s-4，s-5，s-6出现的次数之和。
//初始条件：第一轮的f(1),f(2),f(3),f(4),f(5),f(6)均等于1.
//需要求的是：f(n , n)、 f(n, n+1)....f(n, 6*n)

// leetcode 1155 掷骰子的N中方法
int numRollsToTarget(int d, int f, int target)
{



}



// 携程第一道　分割区间的题　自己有点理解不好
// aabbcddc -> 2,2,4
//int fake_main()
//{
//    string s;
//    cin >> s;
//    unordered_map<char, int> m;
//    unordered_map<char, bool> flag;
//    int sum = 0, cur = 0;
//    vector<int> res;
//    for (int i = 0; i < s.size(); i++)
//        m[s[i]]++;
//    for (int i = 0; i < s.size(); i++) {
//        if (flag.find(s[i]) == flag.end()) {
//            sum += m[s[i]];
//            flag[s[i]] = true;
//        }
//        cur++;
//        if (cur == sum) {
//            res.push_back(cur);
//            cur = 0;
//            sum = 0;
//        }
//    }
//    for (int i = 0; i < res.size(); i++) {
//        if (i != res.size() - 1)
//            cout << res[i] << ',';
//        else
//            cout << res[i] << endl;
//    }
//    return 0;
//}


// 携程第三道　求最短旅游路线　dp
void helper(int idx, int nums, int &res, int cur, vector<vector<pair<int, int>>> &neigh, vector<bool> &flag) {
    if (idx == 0 && flag[idx] == true) {
        if (nums == flag.size())
            res = min(res, cur);
        return;
    }
    for (int i = 0; i < neigh[idx].size(); i++) {
        if (flag[neigh[idx][i].first] == false) {
            flag[neigh[idx][i].first] = true;
            helper(neigh[idx][i].first, nums + 1, res, cur + neigh[idx][i].second, neigh, flag);
            flag[neigh[idx][i].first] = false;
        }
    }
}
int fakemain3() {
    int n, m;
    cin >> n >> m;
    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }
    vector<vector<pair<int, int>>> neigh(n);
    while (m--) {
        int a, b, t;
        cin >> a >> b >> t;
        neigh[a].push_back(make_pair(b, t));
        neigh[b].push_back(make_pair(a, t));
    }
    vector<bool> flag(n, false);
    int res = INT_MAX;
    helper(0, 0, res, 0, neigh, flag);
    if (res == INT_MAX)
        cout << -1 << endl;
    else
        cout << res << endl;
    return 0;
}



// 最长公共子序列(不是子串)
// 其中dp[i][j]表示 A数组前i个和B数组前j个中的满足要求子序列的最长值
int max_common_str1(string& a, string& b)
{
    auto length = a.size() > b.size() ? a.size() : b.size();
    int dp[length+1][length+1];
    memset(dp, 0, sizeof(dp));

    for(int i = 0; i < a.size(); i ++)
        for(int j = 0; j < b.size(); j ++)
        {
            if(a[i] == b[j])
                dp[i+1][j+1] = dp[i][j] + 1;
            else
            {
                dp[i+1][j+1] = max(dp[i][j+1], dp[i+1][j]);
            }
        }
    return dp[a.size()][b.size()];
}

// 最长公共子子数组(也是子串)　leetcode 718
// dp[i][j]表示  以A[i]B[j]为结尾的相同子串的最大长度
int findLength(vector<int>& A, vector<int>& B) {

    auto len1 = A.size();
    auto len2 = B.size();
    auto len = max(len1, len2);

    int dp[len+1][len+1];
    memset(dp, 0, sizeof(dp));
    int max_length = 0;

    for(int i = 0; i < len1; i ++)
        for(int j = 0; j < len2; j ++)
        {
            if(A[i] == B[j])
                dp[i+1][j+1] = dp[i][j] + 1;
            max_length = max(max_length, dp[i+1][j+1]);
        }
    return max_length;
}







/*-----字符串快慢指针类------*/






//string rearrangeString(string s, int k)
//{
//    if (k == 0) {
//        return s;
//    }
//    int len = s.size();
//    string result;
//    map<char, int> hash;                                // map from char to its appearance time
//    for(auto ch: s) {
//        ++hash[ch];
//    }
//    priority_queue<pair<int, char>> que;                // using priority queue to pack the most char first
//    for(auto val: hash) {
//        que.push(make_pair(val.second, val.first));
//    }
//    while(!que.empty()) {
//        vector<pair<int, int>> vec;
//        int cnt = min(k, len);
//        for(int i = 0; i < cnt; ++i, --len) {           // try to pack the min(k, len) characters sequentially
//            if(que.empty()) {                           // not enough distinct charachters, so return false
//                return "";
//            }
//            auto val = que.top();
//            que.pop();
//            result += val.second;
//            if(--val.first > 0) {                       // collect the remaining characters
//                vec.push_back(val);
//            }
//        }
//        for(auto val: vec) {
//            que.push(val);
//        }
//    }
//    return result;
//}



// 360 笔试一面 https://blog.csdn.net/qq_41855420/article/details/92102066
//    int N;
//    int M;
//    cin >> N;
//    cin >> M;
//    vector<vector<int>> blocks(N, vector<int>(M,0));
//    for(int i = 0; i < N; i ++)
//        for(int j = 0; j < M; j ++)
//        {
//            int temp;
//            cin >> temp;
//            blocks[i][j] = temp;
//        }
//
//    int res = 0;
//    for (int row = 0; row < N; row ++)
//        for (int col = 0; col < M; col ++){
//            if (blocks[row][col]) {
//
//                res += 2;
//
//                if (row > 0) {
//                    if (blocks[row][col] > blocks[row - 1][col])
//                        res += blocks[row][col] - blocks[row - 1][col];
//                } else
//                    res += blocks[row][col];
//                if (col > 0) {
//                    if (blocks[row][col] > blocks[row][col - 1])
//                        res += blocks[row][col] - blocks[row][col - 1];
//                } else
//                    res += blocks[row][col];
//                if (row + 1 < N)
//                {
//                    if (blocks[row][col] > blocks[row + 1][col]) {
//                        res += blocks[row][col] - blocks[row + 1][col];
//                    }
//                }
//                else {
//                    res += blocks[row][col];
//                }
//                if (col + 1 < M){
//                    if (blocks[row][col] > blocks[row][col + 1]){
//                        res += blocks[row][col] - blocks[row][col + 1];
//                    }
//                }
//                else {
//                    res += blocks[row][col];
//                }
//            }
//        }
//
//    cout << res;






// 华为笔试第三题 逻辑计算 和 加减乘除类似
// 遇到& 有三种情况 要考虑 & 的优先级
// 第一种遇到正常字符或者（，那么就把这个（）内取值，或者正常数字作为第二个数，
// 接着循环，如果遇到&或者|或者直接到末尾了 表示&该计算了，就把第一个数和第二个数做个&操作，作为外层的第一个数

int dfs_normal(string &s, int start_index, int end_index);
int dfs_kh(int &index, string &s)
{
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
int dfs_normal(string &s, int start_index, int end_index)
{
    int first;
    int second = -1;
    bool fei = false;

    for (int i = start_index; i < end_index; ++i)
    {
        if (s[i] == '(') {
            first = dfs_kh(++i, s);
        }
        else if (s[i] == '&') {
            bool fei2 = false;
            int second2;
            if (fei) {  // 先把左边的项确定好
                first = first ^ 1;
                fei = false;
            }
            int j;
            for (j = i + 1; j < end_index; ++j) {    // 因为&的优先级高 所以内循环 不会跳出去再返回结果
                if (s[j] == '(') {
                    second2 = dfs_kh(++j, s);
                }
                else if (s[j] == '|'||s[j]=='&') {  // 到了另一个判断口　先把当前的处理了　然后退出
                    if (fei2)
                        second2 = second2 ^ 1;
                    first = first & second2;
                    i = j - 1;    //　将坐标退回去
                    break;
                }
                else if (s[j] == '!')
                    fei2 = true;
                else
                    second2 = s[j] - '0';
            }
            // 如果已经到结尾了
            if (j == end_index) {
                first = first & second2;
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










//　这个函数执行5次打印　12345
void test()
{
    static int a = 0;
    a += 1;
    cout << a;
}

// leetcode 864　获取所有钥匙的最短路径
// 广搜的一个经典题
vector<string> maze = {"@.a.#",
                       "###.#",
                       "b.A.B"};

int shortestPathAllKeys(vector<string>& grid)
{
    int start_x = 0;
    int start_y = 0;
    int row = grid.size();
    int col = grid[0].size();
    int n = 0;          // 共有多少把钥匙

    /*find key and lock*/
    for(int i = 0;i < row; ++i){
        for(int j = 0;j < col; ++j){
            if(grid[i][j] >= 'a' && grid[i][j] <= 'z'){
                n++;
            }
            if(grid[i][j] == '@'){
                start_x = i;
                start_y = j;
            }
        }
    }

    int mask = (1<<n) - 1;    // 如果是两把钥匙　那么状态就是　(1<<2)-1 = 011 也就是第0位代表第一把钥匙　第1为代表第二把钥匙
    int visit[30][30][128];   // 2^7 = 128  收集不同的状态　
    int step = -1;
    int d[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
    queue<pair<pair<int,int>,int>> qu;    // 状态变量  用于记录每一步的情况　保证不同分支不会走重复的路

    /*initial*/
    memset(visit,0,sizeof(visit));
    qu.push(make_pair(make_pair(start_x,start_y),0));
    visit[start_x][start_x][0] = true;

    /*get*/
    while(!qu.empty()) {
        int mx = qu.size();
        step++;

        for (int i = 0; i < mx; ++i) {
            int x = qu.front().first.first;
            int y = qu.front().first.second;
            int state = qu.front().second;
            qu.pop();

            if (state == mask) {
                return step;
            }

            for (int j = 0; j < 4; ++j) {
                int x1 = x + d[j][0];
                int y1 = y + d[j][1];
                if (x1 >= 0 && y1 >= 0 && x1 < row && y1 < col) {
                    /*wall*/
                    if (grid[x1][y1] == '#') {
                        continue;
                    } else if (grid[x1][y1] >= 'a' && grid[x1][y1] <= 'f') {
                        /*key*/
                        int currState = state | (1 << (grid[x1][y1] - 'a'));
                        if (!visit[x1][y1][currState]) {
                            visit[x1][y1][currState] = 1;
                            qu.push(make_pair(make_pair(x1, y1), currState));
                        }
                    } else if (grid[x1][y1] >= 'A' && grid[x1][y1] <= 'F') {
                        /*lock*/
                        if (!visit[x1][y1][state]) {
                            if (state & (1 << (grid[x1][y1] - 'A'))) {
                                visit[x1][y1][state] = 1;
                                qu.push(make_pair(make_pair(x1, y1), state));
                            }
                        }
                    } else if (grid[x1][y1] == '.' || grid[x1][y1] == '@') {
                        /*room*/
                        if (!visit[x1][y1][state]) {
                            visit[x1][y1][state] = 1;
                            qu.push(make_pair(make_pair(x1, y1), state));
                        }
                    }

                }
            }
        }
    }
    return -1;
}


// 判断是否平衡二叉树
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
bool isBalanced(TreeNode* root, int& depth)
{
    if(root == nullptr)
    {
        depth = 0;
        return true;
    }
    int left,right;
    if(isBalanced(root->left, left) && isBalanced(root->right, right))
    {
        int diff = left - right;
        if(diff <= 1 && diff >= -1)
        {
            depth = 1 + (left > right ? left : right);  // 一边记录每个树左右子树是否深度一样　一边记录深度
            return true;
        }
    }
    return false;
}
bool isBalanced(TreeNode* root) {

    int depth = 0;
    return isBalanced(root, depth);
}


// 找到一个数组中某两个数只出现一次　本地编译通过但是牛客上无法通过
void FindNumsAppearOnce(vector<int> data,int* num1,int *num2)
{

    set<int> stored_nums;
    for(auto& num: data)
    {
        if(stored_nums.count(num))
            stored_nums.erase(num);
        else
        {
            stored_nums.insert(num);
        }
    }
    num1 = const_cast<int *>(&(*(stored_nums.begin())));
    num2 = const_cast<int *>(&(*(++stored_nums.begin())));
}


// 花光N元的钱 最少能买几件商品 库存不限
// dp是花了多少钱后最少的东西数量
int min_objects(vector<int> prices, int N)
{
    auto len = prices.size();
    vector<int> dp(N+1, -1);
    dp[0] = 0;
    for(int i = 0; i < n; i ++)
        for(int j = prices[i]; j <= N; j ++)
        {
            if(dp[j-prices[i]] != -1)
            {
                if(dp[j] == -1)
                    dp[j] = dp[j-prices[i]] + 1;
                else
                    dp[j] = min(dp[j], dp[j-prices[i]]+1);
            }
        }
    return dp[N];
}


// 剑指offer上的
// 查找排序数组中数字出现的次数　用两个二分查找分别查找最左和最右出现的次数
int getFirstK(vector<int> data, int k, int start, int end)
{
    auto len = data.size();
    if(start > end)
        return -1;
    int mid = (start + end) / 2;
    int mid_data = data[mid];
    if(mid_data == k)
    {
        if((mid > 0 && data[mid - 1] != k) || mid == 0)  // 如果满足第一个出现k的条件
            return mid;
        else
            end = mid - 1;    // 说明第一个k在这个数的左边
    } else if(mid_data > k)
        end = mid - 1;
    else
        start = mid + 1;
    return getFirstK(data, k, start, end);
}
int getLastK(vector<int> data, int k, int start, int end)
{
    auto len = data.size();
    if(start > end)
        return -1;
    int mid = (start + end) / 2;
    int mid_data = data[mid];
    if(mid_data == k)
    {
        if((mid < len-1 && data[mid + 1] != k) || mid == len-1)  // 如果满足最后一个出现k的条件
            return mid;
        else
            start = mid + 1;    // 说明第一个k在这个数的左边
    } else if(mid_data < k)
        start = mid + 1;
    else
        end = mid - 1;
    return getLastK(data, k, start, end);
}
int getNumberOfK(vector<int> data, int k)
{
    auto len = data.size();
    int number = 0;
    if(!data.empty())
    {
        int first = getFirstK(data, k, 0, len-1);
        int last = getLastK(data, k, 0, len-1);
        if(first > -1 && last > -1)
            number = last - first + 1;
    }
    return number;
}


// leetcode 4　寻找两个有序数组的中位数
//寻找a 和 b 数组中，第k个数字
double find_kth(vector<int> a, int a_begin, vector<int> b, int b_begin, int k) {
    //当a 或 b 超过数组长度，则第k个数为另外一个数组第k个数
    if (a_begin >= a.size())
        return b[b_begin + k - 1];
    if (b_begin >= b.size())
        return a[a_begin + k - 1];
    //k为1时，两数组最小的那个为第一个数
    if (k == 1)
        return min(a[a_begin], b[b_begin]);

    int mid_a = INT32_MAX;
    int mid_b = INT32_MAX;
    //mid_a / mid_b 分别表示 a数组、b数组中第 k / 2 个数
    if (a_begin + k / 2 - 1 < a.size())
        mid_a = a[a_begin + k / 2 - 1];
    if (b_begin + k / 2 - 1 < b.size())
        mid_b = b[b_begin + k / 2 - 1];
    //如果a数组的第 k / 2 个数小于b数组的第 k / 2 个数，表示总的第 k 个数位于 a的第k / 2个数的后半段，或者是b的第 k / 2个数的前半段
    //由于范围缩小了 k / 2 个数，此时总的第 k 个数实际上等于新的范围内的第 k - k / 2个数，依次递归
    if (mid_a < mid_b)
        return find_kth(a, a_begin + k / 2, b, b_begin, k - k / 2);
    //否则相反
    return find_kth(a, a_begin, b, b_begin + k / 2, k - k / 2);
}
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
{
    int m = nums1.size();
    int n = nums2.size();
    //处理任何一个nums为空数组的情况
    if (m == 0) {
        if (n % 2 != 0)
            return 1.0 * nums2[n / 2];
        return (nums2[n / 2] + nums2[n / 2 - 1]) / 2.0;
    }
    if (n == 0) {
        if (m % 2 != 0)
            return 1.0 * nums1[m / 2];
        return (nums1[m / 2] + nums1[m / 2 - 1]) / 2.0;
    }
    int total = m + n;
    //总数为奇数，找第 total / 2 + 1 个数
    if ((total & 1) == 1) {
        return find_kth(nums1, 0, nums2, 0, total / 2 + 1);
    }
    //总数为偶数，找第 total / 2 个数和第total / 2 + 1个数的平均值
    return (find_kth(nums1, 0, nums2, 0, total / 2) + find_kth(nums1, 0, nums2, 0, total / 2 + 1)) / 2.0;
}


// leetcode 1027  最长等差数列
// 输入
int longestArithSeqLength(vector<int>& A) {
    if(A.size() <= 2)
        return A.size();
    int res = 0;
    vector<vector<int>> dp(A.size(),vector<int>(20001,1));
    for(int i = 1;i < A.size();i++)
        for(int j = 0;j < i;j++)
        {
            int sub = A[i] - A[j] + 10000;    // 加10000是为了中和负数　然后开辟20000个为了覆盖　-1000 - 1000
            dp[i][sub] = max(dp[i][sub],dp[j][sub] + 1);
            res = max(res,dp[i][sub]);
        }
    return res;
}


// leetcode 俄罗斯信封　降维加最长上升子序列
int maxEnvelopes(vector<vector<int>>& envelopes)
{
    if(envelopes.empty())
        return 0;

    sort(envelopes.begin(), envelopes.end(),
         [](const vector<int>& a, const vector<int>& b){
             if(a[0] == b[0])
                 return a[1] > a[1];
             return a[0] < b[0];
         });
    auto len = envelopes.size();

    vector<int> dp(len + 1, 1);
    int res = dp[0];
    for(int i = 1; i < len; i ++)
        for(int j = 0; j < i; j ++)
        {
            if(envelopes[j][0] < envelopes[i][0] && envelopes[j][1] < envelopes[i][1])
                dp[i] = max(dp[j] + 1, dp[i]);
        }
    for(int i = 1; i < len; i ++)
        res = max(res, dp[i]);
    return res;
}


//int test = 1;
//int &pp = test;
//int* ppp = &test;
// cout << sizeof(pp) << sizeof(ppp);  输出一个4一个8

// 找零钱系列问题，如果物品是固定的，那么可以使用贪心做，如果是动态的，就需要背包做了

