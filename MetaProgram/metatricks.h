//
// Created by prototype on 18-12-15.
//

#ifndef PANCNN_METATRICKS_H
#define PANCNN_METATRICKS_H

#include <iostream>
#include <vector>
#include <memory>

using namespace std;


///*这里定义了一个可以顺序执行的元函数*/
//// 结构体中所有的语句都要看成执行的语句
//template <typename T>
//struct RemoveReferenceConst_{
//private:
//    using inter_type = typename std::remove_reference<T>::type;
//public:
//    using type = typename std::remove_const<inter_type>::type;
//};
//
//template <typename T>
//using RemoveReferenceConst = typename RemoveReferenceConst_<T>::type;
///*这里定义了一个可以顺序执行的元函数*/
//
//
///*C++-14中的特化方式--应用于实现分支*/
////在C++-14中 constexpr可以对non-static member function进行声明
//struct A; struct B;
//
//template <typename T>
//constexpr size_t Fun = 0;
//
//template <>
//constexpr size_t Fun<A> = 1;
//
//template <>
//constexpr size_t Fun<B> = 2;
//
//constexpr size_t h = Fun<A>;
///*C++-14中的特化方式*/
//
//
//
///*--使用if constexpr--作编译期间的条件选择*/
//template <bool Check>
//auto fun()
//{
//    if constexpr (Check)
//    {
//        return (int)3;
//    } else
//    {
//        return (double)2;
//    }
//}
///*--使用if constexpr--作编译期间的条件选择*/
//
//
//
///*--constexpr function不需要function template因为本身就是编译器函数*/
//constexpr auto if_test(bool t)
//{
//    return t?(int)1:(float)2;
//}
///*--但是还有个问题,当编译器不确定t类型的时候这个函数就会在运行期运行*/
//
//
//
///*---在编译器循环执行的代码---1,注意实例爆炸的情况*/
//template <size_t Input>
//constexpr size_t OnesCount = (Input % 2) + OnesCount<(Input / 2)>;
//
//template <> constexpr size_t OnesCount<0> = 0;
//
//// constexpr size_t res = OnesCount<45>;
//
//
//
//
//
///*---在编译器循环执行的代码---2*/
//template <size_t ...Inputs>
//constexpr size_t Accumulate = 0;
//
//template <size_t CurInput, size_t ...Inputs>
//constexpr size_t Accumulate<CurInput, Inputs...>
//        = CurInput + Accumulate<Inputs...>;
///*---在编译器循环执行的代码---*/
////    constexpr size_t res = Accumulate<1,2,3,4,5>;
//
//
//
///*分支选择与短路逻辑*/
//template <size_t N>
//constexpr bool is_odd = ((N%2)==1);
//
//template <bool cur, typename TNext>
//constexpr static bool AndValue = false;
//
//template <typename TNext>
//constexpr static bool AndValue<true, TNext> = TNext::value;
//
//template <size_t N>
//struct AllOdd_{
//    constexpr static bool is_cur_odd = is_odd<N>;
//    constexpr static bool value = AndValue<is_cur_odd, AllOdd_<N-1>>;
//};
///*分支选择与短路逻辑*/
//
//
//int std_move_test();

///*　奇异的递归模板式　*/
//template <typename  D>
//struct Base
//{
//    template <typename TI>
//    void Fun(const TI& input){
//        D* ptr = static_cast<D*>(this);
//        ptr->Imp(input);
//    }
//};
//
//struct Derive : public Base<Derive>
//{
//    template <typename TI>
//    void Imp(const TI& input){
//        cout << input << endl;
//    }
//};



#endif //PANCNN_METATRICKS_H
