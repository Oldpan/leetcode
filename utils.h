//
// Created by prototype on 19-5-23.
//

#ifndef LEETCODE_UTILS_H
#define LEETCODE_UTILS_H

#include <random>
#include <vector>
#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>

#define random(s,e) (rand()%e+s)

using namespace std;

char* number2char(int n);
void my_swap(int& a, int& b);
int partition(vector<int>& data, int start, int end);
void quick_sort(vector<int>& nums, int begin, int end);
void set_example();
void multiset_example();
bool IsBig_Endian();


vector<int> mergeSort(vector<int>& array, int begin, int end);


















#endif //LEETCODE_UTILS_H


