//
// Created by 郭彦宗 on 2019-07-20.
//

#include "test_thread.h"
#include <thread>
#include <mutex>
#include <chrono>
#include <future>
#include <iostream>
#include <unistd.h>

using namespace std;


static void hello_thread()
{
    for(int i = 0; i < 5; i ++)
    {
        cout << "Hello World" << endl;
        sleep(1);
    }
}

static void add_thread(int a,int b)
{
    int c = a + b;
    for(int i = 0; i < 5; i ++)
    {
        cout << "a + b = " << c << endl;
        sleep(1);
    }
}


// 测试两个子进程 对同一个全局变量进行处理 这时候需要同步机制 mutex
int total_number = 100;

static void thread_sub()
{
    for(int i = 0 ; i < 5; i ++)
    {
        total_number --;
        cout << total_number << endl;
        sleep(1);
    }
}

static void thread_add()
{
    for(int i = 0; i < 5; i ++) {
        total_number++;
        cout << total_number << endl;
        sleep(1);
    }
}

mutex mu;  // 线性互斥对象

static void thread_sub_lock()
{
    for(int i = 0 ; i < 5; i ++)
    {
        mu.lock();
        total_number --;
        cout << total_number << endl;
        mu.unlock();
        sleep(1);
    }
}

static void thread_add_lock()
{
    for(int i = 0; i < 5; i ++) {
        mu.lock();
        total_number++;
        cout << total_number << endl;
        mu.unlock();
        sleep(1);
    }
}
std::thread::id main_thread_id = std::this_thread::get_id();

void hello()
{
    std::cout << "Hello Concurrent World\n";
    if (main_thread_id == std::this_thread::get_id())
        std::cout << "This is the main thread.\n";
    else
        std::cout << "This is not the main thread.\n";
}

void pause_thread(int n) {
    std::this_thread::sleep_for(std::chrono::seconds(n));
    std::cout << "pause of " << n << " seconds ended\n";
}

void test_thread_1()
{
    thread t1(hello_thread);
    thread t2(add_thread, 1, 2);
    // 主线程等待子线程运行结束后方可执行下一步 这也是join的作用
    t1.join();
    t2.join();
    // 主线程代码
    cout << "Main Here" << endl;
}

void test_thread_2()
{
    thread t1(hello_thread);
    thread t2(add_thread, 1, 2);
    // 如果使用detach的话，可以使子线程从主线程中分离，独立运行
    t1.detach();
    t2.detach();
    // 主线程代码
    for(int i = 0; i < 5; i ++)
    {
        cout << "Main Here" << endl;
        sleep(1);
    }
}

// 两个子任务竞争一个变量的变化权限 没有上锁 所以比较危险
void test_thread_3()
{
    thread task1(thread_add);
    thread task2(thread_sub);
    task1.detach();
    task2.detach();

    sleep(10);
}

// 这里就加入了锁 可以保证变量
void test_thread_4()
{
    thread task1(thread_add_lock);
    thread task2(thread_sub_lock);
    task1.detach();
    task2.detach();

    sleep(10);
}


void test_thread_5()
{
    std::thread t(hello);
    std::cout << t.hardware_concurrency() << std::endl;                 //可以并发执行多少个(不准确)
    std::cout << "native_handle " << t.native_handle() << std::endl;    //可以并发执行多少个(不准确)
    t.join();
    std::thread a(hello);
    a.detach();
    std::thread threads[5];                         // 默认构造线程

    std::cout << "Spawning 5 threads...\n";
    for (int i = 0; i < 5; ++i)
        threads[i] = std::thread(pause_thread, i + 1);   // move-assign threads
    std::cout << "Done spawning threads. Now waiting for them to join:\n";
    for (auto &thread : threads)
        thread.join();
    std::cout << "All threads joined!\n";
}


// std::packaged_task  可以包裹一个函数, 有点类似std::function，
// 不同之处在于这个可以通过get_future返回std::future对象来获取异步执行的函数结果。
void test_thread_6()
{
    std::packaged_task<int()> task([]()
                                   {
                                       std::cout << "packaged_task start!"<<std::endl;
                                       std::chrono::milliseconds dur(10000);
                                       std::this_thread::sleep_for(dur);
                                       return 10000;
                                   });
    std::future<int> fuResult = task.get_future();
    std::thread t_task(std::move(task));
    t_task.detach();
    std::cout << "detach..." << std::endl;
    std::cout << fuResult.get() << std::endl;
}


// std::async提供异步执行的方法，std::future = std::async(...),
// 函数执行完成后可以通过std::future.get()获取到执行函数的返回值。
void test_thread_7()
{
    std::future<int> fuResult = std::async([]()
   {
       std::this_thread::sleep_for(std::chrono::seconds(10));
       return 1;
   });
    std::cout<<"detach..."<<std::endl;
    std::cout<<fuResult.get()<<std::endl;
}

void test_openmp_1()
{
#pragma omp parallel for
    for (int i = 0; i < 10; i++)
    {
        cout << i << endl;
    }
}


