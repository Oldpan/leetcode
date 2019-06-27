//
// Created by 郭彦宗 on 2019-06-27.
//

#ifndef LEETCODE_DESIGN_PATTERN_H
#define LEETCODE_DESIGN_PATTERN_H

#include <iostream>

// 关于这些代码的讲解网站:https://segmentfault.com/a/1190000010706695


// 造房子时需要一个门. 你是穿上木匠服开始在你家门口锯木头, 搞得一团糟; 还是从工厂里生产一个.
// 简单工厂为用户提供了一个实例, 而隐藏了具体的实例化逻辑.

// 当你创建一个对象, 并非简单拷贝赋值, 牵扯很多其他逻辑时, 就应该把它放到一个专门的工厂中,
// 而不是每次都重复. 这个体现在 C++ 中, 主要就是将new语句的逻辑抽象到一个单例
// 或者如上述例子一样, 扔到一个统一的静态函数中去.

//class IDoor {
//public:
//    virtual float GetWidth() = 0;
//    virtual float GetHeight() = 0;
//};
//
//class WoodenDoor : public IDoor {
//public:
//    WoodenDoor(float width, float height): m_width(width), m_height(height){}
//    float GetWidth() override { return m_width; }
//    float GetHeight() override { return m_height; }
//
//protected:
//    float m_width;
//    float m_height;
//};
//
//class DoorFactory {
//public:
//    static IDoor* MakeDoor(float width, float heigh)
//    {
//        return new WoodenDoor(width, heigh);
//    }
//};


// 如果你主管招聘, 你肯定无法做到什么职位都由你一个人来面试. 根据具体的工作性质, 你需要选择并委托不同的人来按步骤进行面试.
// 一种将实例化逻辑委托给子类的方法
// 这个 好像是 奇异的递归模板

class IInterviewer
{
public:
    virtual void askQuestions() = 0;
};

class Developer : public IInterviewer
{
public:
    void askQuestions() override {
        std::cout << "Asking about design patterns!" << std::endl;
    }
};

class CommunityExecutive : public IInterviewer
{
public:
    void askQuestions() override {
        std::cout << "Asking about community building!" << std::endl;
    }
};

class HiringManager
{
public:
    void takeInterview() {
        IInterviewer* interviewer = this->makeInterviewer();
        interviewer->askQuestions();
    }

protected:
    virtual IInterviewer* makeInterviewer() = 0;
};

template <typename Interviewer>
class OtherManager : public HiringManager {
protected:
    IInterviewer* makeInterviewer() override {
        return new Interviewer();
    }
};

// 接着简单工厂里的案例. 根据实际需要, 您可以从木门商店获得木门, 从铁门商店获得铁门, 从相关商店获得 PVC 门. 除此之外, 你还需要不同专业的人,
// 来帮你装门, 木门需要木匠, 铁门需要焊工. 可以看到, 门之间存在着一定的对应依赖关系. 木门-木匠, 铁门-焊工, 等等.

class IDoor {
public:
    virtual void GetDescription() = 0;
};

class WoodenDoor : public IDoor {
public:
    void GetDescription() override {
        std::cout << "I am a wooden door" << std::endl;
    }
};

class IronDoor : public IDoor {
public:
    void GetDescription() override {
        std::cout << "I am a iron door" << std::endl;
    }
};

class IDoorFittingExpert {
public:
    virtual void GetDescription() = 0;
};

class Carpenter : public IDoorFittingExpert {
    void GetDescription() override {
        std::cout << "I can only fit wooden doors" << std::endl;
    }
};

class Welder : public IDoorFittingExpert {
    void GetDescription() override {
        std::cout << "I can only fit iron doors" << std::endl;
    }
};

class IDoorFactory {
public:
    virtual IDoor* MakeDoor() = 0;
    virtual IDoorFittingExpert* MakeFittingExpert() = 0;
};

template <typename Door, typename DoorFittingExpert>
class DoorFactory : public IDoorFactory {
public:
    IDoor* MakeDoor() override {
        return new Door();
    }
    IDoorFittingExpert* MakeFittingExpert() override {
        return new DoorFittingExpert();
    }
};



// 类似于TVM中添加op的一种方式 *
// 生成器模式的本质, 就是将构造函数中的参数列表方法化. 长长的参数列表, 无论是面向对象还是函数式编程, 都是大忌. 该模式主要就是为了解决该问题.
// 函数式编程中对该问题的解决方式是: 柯里化, 其本质与生成器模式是一样的.

class Burger {
public:
    class BurgerBuilder;
    void showFlavors() {
        std::cout << size_;
        if (cheese_) std::cout << "-cheese";
        if (peperoni_) std::cout << "-peperoni";
        if (lettuce_) std::cout << "-lettuce";
        if (tomato_) std::cout << "-tomato";
        std::cout << std::endl;
    }
private:
    Burger(int size): size_(size) {}

    int size_ = 7;
    bool cheese_ = false;
    bool peperoni_ = false;
    bool lettuce_ = false;
    bool tomato_ = false;
};

class Burger::BurgerBuilder {
public:
    BurgerBuilder(int size) { burger_ = new Burger(size); }
    BurgerBuilder& AddCheese() { burger_->cheese_ = true; return *this; }
    BurgerBuilder& AddPepperoni() { burger_->peperoni_ = true; return *this; }
    BurgerBuilder& AddLettuce() { burger_->lettuce_ = true; return *this; }
    BurgerBuilder& AddTomato() { burger_->tomato_ = true; return *this; }
    Burger* Build() { return burger_; }
private:
    Burger* burger_;
};




class ILion {
public:
    virtual void Roar() {
        std::cout << "I am a Lion" << std::endl;
    }
};

class Hunter {
public:
    void Hunt(ILion& lion) {
        lion.Roar();
    }
};

class WildDog
{
public:
    void Bark() {
        std::cout << "I am a wild dog." << std::endl;
    }
};

//! now we added a new class `WildDog`, the hunter can hunt it also.
//! But we cannot do that directly because dog has a different interface.
//! To make it compatible for our hunter, we will have to create an adapter.

class WildDogAdapter : public ILion {
public:
    WildDogAdapter(WildDog& dog): dog_(dog) {}
    void Roar() override {
        dog_.Bark();
    }
private:
    WildDog& dog_;
};



#endif //LEETCODE_DESIGN_PATTERN_H
