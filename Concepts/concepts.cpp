#include "concepts.h"

using namespace std;

// C++是一种静态数据类型语言，它的类型检查发生在编译时

// 类型float和double 分别有7个和16个有效位 一般来说执行浮点数使用double，因为float通常精度不够而且
// 双精度浮点数和单精度浮点数的计算代价相差无几

// 位于头文件的代码一般来说不应该使用using声明。这是因为头文件的内容会拷贝到所有引用它的文件中去
// 如果头文件里有某个using声明，那么每个使用了该头文件的文件都还有这个声明，对于某些程序可能回造成冲突

// 类型转换 不要混用符号类型和无符号类型 因为带符号数会自动地转换成无符号数 下面两者加起来的值是未知的
// test_a*test_b 值为 4294967295
int test_a = -1;
unsigned int test_b = 1;

// 字符和字符串类型 字符串会在后头多一个 '\0'空字符
char a = 'a';
char a_str[2] = "a";

// 列表初始化，这个是C11新出来的标准 以下四种都代表一个方式
//int unit_sold = 0;
//int unit_sold = {0};
//int unit_sold(0);
int unit_sold{0};




// 为什么引用如此好用 引用必须被初始化 引用只能绑定在对象上，不能与某个字面值或者某个表达式的计算结果绑定在一起
//int temp = 1;
//int& temp1 = temp;
////如果换成指针 那么取值的还需要加上 *才可以取值 赋值也同样如此
//int* temp2 = &temp;


/*-- for loop --*/
//std::vector<int> v = {0, 1, 2, 3, 4, 5};
//void for_loop_test()
//{
//    for (const int& i : v) // access by const reference
//        std::cout << i << ' ';
//
//    for (auto i : v) // access by value, the type of i is int
//        std::cout << i << ' ';
//
//    for (auto&& i : v) // access by forwarding reference, the type of i is int&
//        std::cout << i << ' ';
//
//    const auto& cv = v;
//
//    for (auto&& i : cv) // access by f-d reference, the type of i is const int&
//        std::cout << i << ' ';
//
//    for (int n : {0, 1, 2, 3, 4, 5}) // the initializer may be a braced-init-list
//        std::cout << n << ' ';
//
//    int a[] = {0, 1, 2, 3, 4, 5};
//    for (int n : a) // the initializer may be an array
//        std::cout << n << ' ';
//
//    for (int n : a)
//        std::cout << 1 << ' '; // the loop variable need not be used
//}


/*-- const-, volatile-, and ref-qualified member functions --*/
//struct Array {
//    std::vector<int> data;
//    Array(int sz) : data(sz) {}
//    // const member function
//    int operator[](int idx) const {
//        // this has type const Array*
//        return data[idx]; // transformed to (*this).data[idx];
//    }
//    // non-const member function
//    int& operator[](int idx) {
//        // this has type Array*
//        return data[idx]; // transformed to (*this).data[idx]
//    }
//};
//int main()
//{
//    Array a(10);
//    a[1] = 1; // OK: the type of a[1] is int&
//    const Array ca(10);
//    ca[1] = 2; // Error: the type of ca[1] is int
//}




// [](int x, int y) -> int { int z = x + y; return z; } 匿名函数


/*---类的隐式类型转换---*/
//class Value{
//public:
//    explicit Value(int value):value_(value){}
//    explicit operator double () const;
//
//private:
//    int value_;
//};
//
//Value::operator double() const {
//    return static_cast<double>(value_);
//}
//
//Value tt(5);
//double temp = (double)tt * 0.5;


///*-- 变长参数函数 --*/
//int test(int count, ...)
//{
//    va_list args;
//    va_start(args, count);
//    for(int i = 0; i < count; i++)
//    {
//        int arg = va_arg(args, int);
//        cout << i << " " << arg << endl;
//    }
//
//    va_end(args);
//    return 0;
//}
//
//test(3,1,2,3);

// try catch

// 异常既然是一份数据，那么就应该有数据类型。C++ 规定，异常类型可以是 int、char、float、bool 等基本类型，
// 也可以是指针、数组、字符串、结构体、类等聚合类型。C++ 语言本身以及标准库中的函数抛出的异常，
// 都是 exception 类或其子类的异常。也就是说，抛出异常时，会创建一个 exception 类或其子类的对象。






#ifdef ASSIGNMENT_OPERATOR  // assignment operator

/*- tutorial about 赋值运算符函数 ---*/
class CMyString{
public:
    explicit CMyString(char* pData = nullptr);
    CMyString(const CMyString& str);
    ~CMyString(void);

    CMyString& operator = (const CMyString& str);

private:
    char* m_pdata;
};

CMyString::CMyString(char *pData)
{
    if(pData == nullptr)
    {
        m_pdata = new char[1];
        m_pdata[0] = '\0';
    }
    else
    {
        int length = strlen(pData);
        m_pdata = new char[length + 1];
        strcpy(m_pdata, pData);
    }
}


CMyString::CMyString(const CMyString &str)
{
    int length = strlen(str.m_pdata);
    m_pdata = new char[length + 1];
    strcpy(m_pdata, str.m_pdata);
}

CMyString::~CMyString()
{
    delete[] m_pdata;
}


CMyString& CMyString::operator=(const CMyString& str)
{

    /*-- a solution --*/
//    if(this == &str)
//        return *this;
//
//    delete []m_pdata;
//    m_pdata = nullptr;
//
//    m_pdata = new char[strlen(str.m_pdata)+1];
//    strcpy(m_pdata,str.m_pdata);
//
//    return *this;


    /*-- better solution --*/
    if(this != &str)
    {
        CMyString strTemp(str);

        char* pTemp = strTemp.m_pdata;
        strTemp.m_pdata = m_pdata;
        m_pdata = pTemp;
    }

    return *this;
}

#endif

#ifdef FINAL_AND_OVERRIDE   // final and override

class Base
{
public:
	virtual void pig() {}
	virtual void dog() {}
};

class Derived : public Base
{
public:
	//二者都试图重写父类虚函数
	virtual void pil() override final {}   // name mismatch , error
	virtual void dol() final {}		       //no error but not right
};

#endif

#ifdef EXPLICIT_KEY_WORD    // explicit key word

class A
{
public:
    //这里用explicit关键词来修饰类构造函数.
    explicit A(int i = 5, int j = 10)
    {
        m_a = i;
        m_b = j;
    }
private:
    int m_a;
    int m_b;
};


A s;
//这样直接赋值,会被提示错误,因为explicit抑制隐式转换的进行
s = 10;//这样会报错!!!
//当然显示转换还是可以的.
s = A(20);

#endif

#ifdef REFLECTION_API      // Relection API

/*反射机制*/
/*
 * 可以使用map字符从到函数指针再到映射
 * 工厂类提供字符串与函数指针到注册关系
 * 工厂模式根据不同的字符串构造不同的类对象
 * */
typedef void* (*create_fun)();

class ClassFactory{
public:
    ~ClassFactory() = default;;
    void* getClassByName(const std::string &name){
        auto it = my_map.find(name);
        if (it == my_map.end()) { return nullptr;}

        create_fun fun = it->second;
        if (!fun) { return nullptr;}

        return fun();
    }

    void registClass(const std::string &name, create_fun fun){
            my_map[name] = fun;
    }

    static ClassFactory& getInstance(){
            static ClassFactory fac;
            return fac;
    }


private:
    ClassFactory() = default;;
    std::map<std::string, create_fun> my_map;
};

#endif

