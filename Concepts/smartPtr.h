//
// Created by 郭彦宗 on 2019-07-20.
//

// 这里提供演示函数 实现简单的智能指针

template<class T>
class SharpedPtr
{
public:
    SharpedPtr(T* ptr = 0)          //构造函数
            :_ptr(ptr)
            , _pCount(nullptr)
    {
        if (ptr)
        {
            _pCount = new int(1);
        }
    }
    SharpedPtr(const SharpedPtr<T>& ap)//拷贝构造
            :_ptr(ap._ptr)
            , _pCount(ap._pCount)
    {
        if (_ptr)
        {
            ++UseCount();
        }
    }
    //ap1 = ap2;赋值运算符重载
    //①ap1内部封装的指针为空
    //②ap1独占一块空间
    //③ap1与其他对象共享一块空间
    SharpedPtr& operator=(const SharpedPtr<int>& ap)
    {
        if (this != &ap)
        {
            if (_ptr)
            {
                Release();
            }
            //ap1与其他对象共享一块空间
            _ptr = ap._ptr;
            _pCount = ap._pCount;
            ++UseCount();
        }
        return *this;
    }
    //析构函数
    ~SharpedPtr()
    {
        Release();
    }
    //检查引用计数并释放空间
    void Release()
    {
        if (0 == --UseCount())
        {
            delete _pCount;
            _pCount = nullptr;
            delete _ptr;
            _ptr = nullptr;
        }
    }
    //获取引用计数
    int& UseCount()
    {
        return *_pCount;
    }
//为了使其更像一个指针，所完成的基本操作
    T* operator->()
    {
        return _ptr;
    }

    T& operator*()
    {
        return *_ptr;
    }
private:
    T* _ptr;
    int* _pCount;
};





