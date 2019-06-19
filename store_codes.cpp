//
// Created by prototype on 19-5-8.
//



// 华为的题 分苹果,将3个苹果分给2个小朋友 将分法打印出来
/*
 * input:
 *  3 2
 * output
    4
    ***|
    **|*
    *|**
    |***
 * */


//using namespace std;
//void dfs(const int &n, int k, vector<int>&choose) {
//    if (k == 0) {
//        for (int i = 0; i <= n; ++i) {
//            int c = choose[i];
//            while (c > 0) {
//                cout << '|';
//                c--;
//            }
//            if (i != n)
//                cout << '*';
//        }
//        cout << endl;
//        return;
//    }
//    for (int i = n; i >= 0; --i) {
//        choose[i]++;
//        dfs(n, k - 1, choose);
//        choose[i]--;
//    }
//}
//
//int main() {
//    int n, k;
//    cin >> n >> k;
//    int num_of_pack = pow(n + 1, k - 1);
//    cout << num_of_pack<<endl;
//    vector<int>choose(n + 1, 0);
//    dfs(n, k - 1, choose);
//    return 0;
//}