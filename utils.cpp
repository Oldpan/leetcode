//
// Created by prototype on 19-5-23.
//



#include "utils.h"

using namespace std;


// leetcode 406 解法和用法好好看下
vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {

    // 匿名函数
    sort(people.begin(),people.end(),[](const auto& a,const auto& b){
        return a[0]>b[0] || (a[0]==b[0] && a[1]<b[1]);
    });

    vector<vector<int> > res;

    for(auto itm:people){
        res.insert(res.begin()+itm[1],itm);
    }
    return res;

}


// 测试set插入时候的比较
class Envelopes{

public:
    Envelopes(int id,int w,int h):_id(id), _w(w), _h(h){};
    bool operator < (const class Envelopes & right) const
    {
        if(this->_id == right._id)
            return false;
        else
        {
            if(this->_w != right._w && this->_h != right._h)
            {
                if(this->_w < right._w && this->_h < right._h)
                    return true;
                else
                    return this->_id < right._id;

            } else{

                return this->_id < right._id;
            }

        }

    }

public:

    int _id;

private:

    int _w;
    int _h;

};

// c++读取以逗号为分隔符的一串数字
void read_num()
{
    string s;
    vector<int> v;
    getline(cin, s);
    istringstream is(s);
    int inter;
    char ch;
    while (is >> inter)
    {
        v.push_back(inter);
        is >> ch;
    }
    for(int i=0;i<v.size();i++)
        cout<<v[i]<<" ";
    cout<<endl;
}


/*--------------------------------经典的背包问题-------------------------------*/





/*------------------排序集合-------------------*/

// 归并排序
// 这个就是简单的将两个数组进行合并
static vector<int> my_merge(vector<int> left, vector<int> right)
{
    vector<int> result;
    int count_l = 0;
    int count_r = 0;

    while(count_l < left.size() && count_r < right.size())
    {
        if(left[count_l] < right[count_r])
            result.push_back(left[count_l++]);
        else
            result.push_back(right[count_r++]);
    }

    while(count_l < left.size())
        result.push_back(left[count_l++]);
    while(count_r < right.size())
        result.push_back(right[count_r++]);

    return result;
}


vector<int> mergeSort(vector<int>& array, int begin, int end)
{
    if(end - begin < 2)
        return vector<int>(array.begin()+begin, array.begin()+end);

    int mid = begin + (end - begin) / 2;

    return my_merge(mergeSort(array, begin, mid),
                    mergeSort(array, mid, end));
}




// 堆排序
// 调整数组中index位置的数组 使其满足最小根的性质
void heap_insert(vector<int>& array, int index)
{
    while (array[index] > array[(index-1)/2])  // 当子树大于父子树则
    {
        my_swap(array[index], array[(index-1)/2]);
        index = (index - 1)/2;  // 切换到 父子树
    }
}

// 将从 0 到 headsize 的数组转化为最大堆
void heapify(vector<int>& array, int heapsize)
{
    for(int i = 0; i < heapsize; i ++)
        heap_insert(array, i);
}


void heapSort(vector<int>& array)
{
    if(array.empty() || array.size() < 2)
        return;

    for(int i = 0; i < array.size(); i ++)
    {
        heap_insert(array, i);
    }

    int heapsize = static_cast<int>(array.size());
    my_swap(array[0], array[heapsize-1]);
    heapsize --;

    while (heapsize > 0){
        heapify(array, heapsize);
        my_swap(array[0], array[heapsize-1]);
        heapsize --;
    }
}




//  大端模式，是指数据的高字节保存在内存的低地址中，而数据的低字节保存在内存的高地址中，这样的存储模式有点儿类似于把数据当作字符串顺序处理：
// 地址由小向大增加，而数据从高位往低位放；这和我们的阅读习惯一致。
//  小端模式，是指数据的高字节保存在内存的高地址中，而数据的低字节保存在内存的低地址中，
// 这种存储模式将地址的高低和数据位权有效地结合起来，高地址部分权值高，低地址部分权值低。
/*--------------------------------判断大小端----------------------------------*/

bool IsBig_Endian()
{
    unsigned short test = 0x1234;
    if(*( (unsigned char*) &test ) == 0x12)
        return true;
    else
        return false;
}


// atoi 字符串变数字  leetcode中有原题

/*-------------------------------数字变字符串----------------------------------*/
// 使用 to_string函数 也可以实现 数字变string
char* number2char(int n)
{
    static char strN[50];
    sprintf(strN, "%d", n);     // 默认会在char后面补 \0 字符串结束符
    return strN;
}
//可以 int test = 123;
//    char* temp = number2char(test);
//    string tempp = static_cast<string>(temp);

/*--------------------------------快速交换-----------------------------------*/

void my_swap(int& a, int& b)
{
    int temp;
    temp = a^b;
    a = temp^a;
    b = temp^b;
}

// 用加法完成交换的功能
void my_swap_with_add(int& a, int& b)
{
    a = a + b;
    b = a - b;
    a = a - b;
}

/*-----模仿迭代器-----*/
// 写法1
int sum_1(int* begin, int* end){
    int n = end - begin;
    int ans = 0;
    for(int i = 0; i < n; i ++)
        ans += begin[i];
    return ans;
}

// 写法2更高级点，事实上也更具一般性
int sum_2(int *begin, int* end){
    int *p = begin;
    int ans = 0;
    for(int *p = begin; p != end; p++)
        ans += *p;
    return ans;
}
// 调用的时候
//sum(a, a+10);     // 计算长度为10的数组a的和
//sum(a+i, a+j+1);  // 计算a[i],a[i+1],...a[j]的和


/*-----------------------------快速排序的核心代码-----------------------------------*/

int partition(vector<int>& data, int start, int end)
{
    auto length = data.size();
    if(data.empty() || start < 0 || end >= length)
        return -1;

    int index = random(start, end); // 随机函数慎用 直接选取第一个值充当index也行
    my_swap(data[index], data[end]);

    int small = start - 1;
    for(index = start; index < end; index ++)
    {
        if(data[index] < data[end])
        {
            ++ small;
            if(small != index)
                my_swap(data[index], data[small]);

        }

    }
    ++ small;
    my_swap(data[small], data[end]);

    return small;
}

void quick_sort(vector<int>& nums, int begin, int end)
{
    if(begin == end)
        return ;
    int index = partition(nums, begin, end);
    if(index < end)
        quick_sort(nums, begin, index - 1);
    if(index > begin)
        quick_sort(nums, index + 1, end);
}



/*-------------------------------Set与Multiset----------------------------------*/
void set_example()
{
    /*type of the collection:
           *-no duplicates
           *-elements are integral values
           *-descending order
           */
    typedef set<int,less<int> > IntSet;

    IntSet coll1;         // empty set container

    //insert elements in random order
    coll1.insert(4);
    coll1.insert(3);
    coll1.insert(5);
    coll1.insert(1);
    coll1.insert(6);
    coll1.insert(2);
    coll1.insert(5);

    //iterate over all elements and print them
    IntSet::iterator pos;
    for (pos = coll1.begin(); pos != coll1.end(); ++pos) {
        cout << *pos << ' ';
    }
    cout << endl;

    //insert 4 again and process return value
    pair<IntSet::iterator,bool> status = coll1.insert(4);
    if (status.second) {
        cout << "4 inserted as element "
             << distance (coll1.begin(),status. first) + 1
             << endl;
    }
    else {
        cout << "4 already exists" << endl;
    }

    //assign elements to another set with ascending order
    set<int> coll2(coll1.begin(),
                   coll1.end());

    //print all elements of the copy
    copy (coll2.begin(), coll2.end(),
          ostream_iterator<int>(cout," "));
    cout << endl;

    //remove all elements up to element with value 3
    coll2.erase (coll2.begin(), coll2.find(3));

    //remove all elements with value 5
    int num;
    num = coll2.erase (5);
    cout << num << " element(s) removed" << endl;

    //print all elements
    copy (coll2.begin(), coll2.end(),
          ostream_iterator<int>(cout," "));
    cout << endl;

}

void multiset_example()
{
    /*type of the collection:
       *-duplicates allowed
       *-elements are integral values
       *-descending order
       */
    typedef multiset<int,greater<int> > IntSet;

    IntSet coll1;      // empty multiset container

            //insert elements in random order
    coll1.insert(4);
    coll1.insert(3);
    coll1.insert(5);
    coll1.insert(1);
    coll1.insert(6);
    coll1.insert(2);
    coll1.insert(5);

    //iterate over all elements and print them
    IntSet::iterator pos;
    for (pos = coll1.begin(); pos != coll1.end(); ++pos) {
        cout << *pos << ' ';
    }
    cout << endl;

    //insert 4 again and process return value
    IntSet::iterator ipos = coll1.insert(4);
    cout << "4 inserted as element "
         << distance (coll1.begin(),ipos) + 1
         << endl;

    //assign elements to another multiset with ascending order
    multiset<int> coll2(coll1.begin(),
                        coll1.end());

    //print all elements of the copy
    copy (coll2.begin(), coll2.end(),
          ostream_iterator<int>(cout," "));
    cout << endl;

    //remove all elements up to element with value 3
    coll2.erase (coll2.begin(), coll2.find(3));            // default is ascending

    //remove all elements with value 5
    int num;
    num = static_cast<int>(coll2.erase (5));
    cout << num << " element(s) removed" << endl;

    //print all elements
    copy (coll2.begin(), coll2.end(),
          ostream_iterator<int>(cout," "));
    cout << endl;

}


void test_array_address()
{
    int *p[2];   // p是包含两个元素的指针数组，指针指向的是int型
    int a[3] = {1,2,3};
    int b[4] = {4,5,6,7};
    p[0] = a;
    p[1] = b;
    for(int i = 0; i < 3; i ++)
        cout << *p[0] + i << endl;   // cout << **p + i;
    for(int j = 0; j < 4; j ++)
        cout << *p[1] + j << endl;

    int (*pp)[2];    // 它相当于一个二维数组的用法，只是它是一个n行2列的数组
    int bb[3][2] = {{1,2},{3,4},{5,6}};
    pp = bb;
    for(int i = 0; i < 3; i ++)
        for(int j = 0; j < 2; j ++)
            cout << pp[i][j];  // cout << *(*(p+i)+j);


    int ** array;    // 为行数确定、列数不确定，即为2*n型的
    array = new int*[2];
    array[0] = a;   // *array = a;
    array[1] = b;   // *(array+1) = b;
    for(int i = 0; i < 3; i ++)
        cout << array[0][i];  // cout << *array[0] + i;
    for(int j = 0; j < 4; j ++)
        cout << array[1][j];  // cout << *array[1] + j;
}

// 通过这些信息可以打印我们的系统运行时候的错误信息位置
void print_information()
{
    printf("当前源代码函数名：__FUNCTION__==%s\n",__FUNCTION__);
    printf("当前源代码行号：__LINE__==%d\n",__LINE__);
    printf("当前源代码文件名：__FILE__==%s\n",__FILE__);
    printf("当前源代码文件名,去掉路径：__FILE__==%s\n",filename(__FILE__));
    printf("当前编译日期〔注意和当前系统日期区别开来〕:__DATE__==%s\n",__DATE__);
    printf("当前编译时间〔注意和当前系统日期区别开来〕:__TIME__==%s\n",__TIME__);
    printf("当前系统时间戳：__TIMESTAMP__==%s\n",__TIMESTAMP__);
    printf("当要求程序严格遵循ANSIC标准时该标识符被赋值为1:__STDC__==%d\n",__STDC__);
    printf("当用C++编译程序编译时，标识符__cplusplus就会被定义:__cplusplus==%ld\n",__cplusplus);
}



/*-----------------------------并查集-----------------------------------*/
// 在code.cpp中写了代码
//int pre[200]; //存放第i个元素的父节点
//
//int unionsearch(int root) //查找根结点
//{
//    int son, tmp;
//    son = root;
//    while(root != pre[root]) //寻找根结点
//        root = pre[root];
//    while(son != root)   //路径压缩
//    {
//        tmp = pre[son];
//        pre[son] = root;
//        son = tmp;
//    }
//    return root;
//}
//
//void join(int root1, int root2)  //判断是否连通，不连通就合并
//{
//    int x, y;
//    x = unionsearch(root1);
//    y = unionsearch(root2);
//    if(x != y)                  //如果不连通，就把它们所在的连通分支合并
//        pre[x] = y;
//}
//
//int findCircleNum(vector<vector<int>>& M)
//{
//    auto row = M.size();
//    auto col = M[0].size();
//    int res = 0;
//    unordered_map<int, int> friends;
//    for(int i = 0; i < 200; i ++)
//        pre[i] = i;
//
//    for(int i = 0; i < row; i++)
//        for(int j = 0; j < col; j ++)
//        {
//            if(M[i][j] == 1)
//                join(i,j);
//        }
//
//    for(int i = 0; i < row; i ++)
//    {
//        if(!friends.count(pre[i]))
//            friends.insert({i,1});
//    }
//
//    res = friends.size();
//    return res;
//}







