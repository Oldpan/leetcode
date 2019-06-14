#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <set>
#include <map>
#include <deque>
#include <queue>

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


int main() {

    vector<vector<int>> temp = {{7,0}, {4,4}, {7,1}, {5,0}, {6,1}, {5,2}};

    reconstructQueue(temp);



    return 0;


}