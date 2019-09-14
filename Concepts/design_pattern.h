//
// Created by 郭彦宗 on 2019-06-27.
//

#ifndef LEETCODE_DESIGN_PATTERN_H
#define LEETCODE_DESIGN_PATTERN_H

#include <iostream>
#include <vector>
#include <functional>

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


/*----------------------------------单例---------------------------------------------*/
// 确保一个特定类的一个对象, 只能创建一次.
// 实际上, 单例模式常被认为是反模式, 要避免过度使用. 它本质上类似全局变量, 可能会造成耦合度过高的问题,
// 也可能给调试带来困难，故而一定要谨慎使用

class President {
public:
    static President& GetInstance() {
        static President instance;  // 因为是static所以只能创建一次　
        return instance;
    }

    President(const President&) = delete;                // 禁止使用编译器默认生成的函数
    President& operator=(const President&) = delete;     // 禁止使用编译器默认生成的函数

private:
    President() {}                      //
};



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

/*-------------------------适配器---------------------------*/
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


/*-------------------------观察者---------------------------*/
// 又被称为发布-订阅模式. 但无论叫什么, 其实本质都是注入+回调. 订阅是注入的时机,
// 发布是回调的时机. 观察是注入的时机, 通知是回调的时机. 在实践中, 通常会维护一个订阅列表,
// 有点类似邮件列表. 发布通知时, 会迭代每一个注入对象, 并执行回调.

class JobPost {
public:
    JobPost(const std::string& title): title_(title) {}
    const std::string& GetTitle() const { return title_; }
private:
    std::string title_;
};

class IObserver {
public:
    virtual void OnJobPosted(const JobPost& job) = 0;
};

class JobSeeker : public IObserver {
public:
    JobSeeker(const std::string& name): name_(name) {}
    void OnJobPosted(const JobPost &job) override {
        std::cout << "Hi " << name_ << "! New job posted: " << job.GetTitle() << std::endl;
    }
private:
    std::string name_;
};

class IObservable {
public:
    virtual void Attach(IObserver& observer) = 0;
    virtual void AddJob(const JobPost& jobPosting) = 0;
protected:
    virtual void Notify(const JobPost& jobPosting) = 0;
};

class JobPostings : public IObservable {
public:
    void Attach(IObserver& observer) override {  // 这里注入信息
        observers_.emplace_back(observer);
    }
    void AddJob(const JobPost &jobPosting) override {  // 发布就会有回调
        Notify(jobPosting);
    }
private:
    void Notify(const JobPost &jobPosting) override {
        for (IObserver& observer : observers_)
            observer.OnJobPosted(jobPosting);   // 回调到对象的函数中
    }

    std::vector<std::reference_wrapper<IObserver> > observers_;  // 这个好像是因为vector中不支持元素是引用
};


/*-----------------------------访问者---------------------------------*/
// 访问者模式允许你为对象们增加更多的操作, 却不必修改它们.

class AnimalOperation;

// visitee
class Animal {
public:
    virtual void Accept(AnimalOperation& operation) = 0;
};

class Monkey;
class Lion;
class Dolphin;

// visitor
class AnimalOperation {
public:
    virtual void visitMonkey(Monkey& monkey) = 0;
    virtual void visitLion(Lion& lion) = 0;
    virtual void visitDolphin(Dolphin& dolphin) = 0;
};

class Monkey : public Animal {
public:
    void Shout() { std::cout << "Ooh oo aa aa!" << std::endl; }
    void Accept(AnimalOperation& operation) override { operation.visitMonkey(*this); }
};

class Lion : public Animal {
public:
    void Roar() { std::cout << "Roaaar!" << std::endl; }
    void Accept(AnimalOperation& operation) override { operation.visitLion(*this); }
};

class Dolphin : public Animal {
public:
    void Speak() { std::cout << "Tuut tuttu tuutt!" << std::endl; }
    void Accept(AnimalOperation& operation) override { operation.visitDolphin(*this); }
};

class Speak : public AnimalOperation {
public:
    void visitMonkey(Monkey& monkey) override { monkey.Shout(); }
    void visitLion(Lion& lion) override { lion.Roar(); }
    void visitDolphin(Dolphin& dolphin) override { dolphin.Speak(); }
};

/*----------------------------桥接器－－－－－－－－－－－－－－－－－－－－－－*/
class ITheme {
public:
    virtual std::string GetColor() = 0;
};

class DarkTheme : public ITheme {
public:
    std::string GetColor() override { return "Dark Black"; }
};

class LightTheme : public ITheme {
public:
    std::string GetColor() override { return "Off white"; }
};

class AquaTheme : public ITheme {
public:
    std::string GetColor() override { return "Light blue"; }
};

class IWebPage {
public:
    IWebPage(ITheme& theme) : theme_(theme) {}
    virtual std::string GetContent() = 0;
protected:
    ITheme& theme_;
};

class About : public IWebPage {
public:
    About(ITheme& theme) : IWebPage(theme) {}
    std::string GetContent() override {
        return "About page in " + theme_.GetColor();
    }
};

class Careers : public IWebPage {
public:
    Careers(ITheme& theme) : IWebPage(theme) {}
    std::string GetContent() override {
        return "Careers page in " + theme_.GetColor();
    }
};


/*---------------------------组成--------------------*/
class Employee {
public:
    Employee(const std::string& name, float salary): name_(name), salary_(salary) {}
    virtual std::string GetName() { return name_; }
    virtual float GetSalary() { return salary_; }

protected:
    float salary_;
    std::string name_;
};

class mDeveloper : public Employee {
public:
    mDeveloper(const std::string& name, float salary) : Employee(name, salary) {}
};

class Designer : public Employee {
public:
    Designer(const std::string& name, float salary) : Employee(name, salary) {}
};

class Organization {
public:
    void AddEmployee(const Employee& employee) {
        employees_.push_back(employee);
    }
    float GetNetSalaries() {
        float net_salary = 0;
        for (auto&& employee : employees_) {
            net_salary += employee.GetSalary();
        }
        return net_salary;
    }

private:
    std::vector<Employee> employees_;
};

/*----------------------装饰器----------------------*/

class ICoffee {
public:
    virtual float GetCost() = 0;
    virtual std::string GetDescription() = 0;
};

class SimpleCoffee : public ICoffee {
public:
    float GetCost() override { return 10; }
    std::string GetDescription() override { return "Simple coffee"; }
};

class CoffeePlus : public ICoffee {
public:
    CoffeePlus(ICoffee& coffee): coffee_(coffee) {}
    virtual float GetCost() = 0;
    virtual std::string GetDescription() = 0;
protected:
    ICoffee& coffee_;
};

class MilkCoffee : public CoffeePlus {
public:
    MilkCoffee(ICoffee& coffee): CoffeePlus(coffee) {}
    float GetCost() override { return coffee_.GetCost() + 2; }
    std::string GetDescription() override { return coffee_.GetDescription() + ", milk"; }
};

class WhipCoffee : public CoffeePlus {
public:
    WhipCoffee(ICoffee& coffee): CoffeePlus(coffee) {}
    float GetCost() override { return coffee_.GetCost() + 5; }
    std::string GetDescription() override { return coffee_.GetDescription() + ", whip"; }
};

class VanillaCoffee : public CoffeePlus {
public:
    VanillaCoffee(ICoffee& coffee): CoffeePlus(coffee) {}
    float GetCost() override { return coffee_.GetCost() + 3; }
    std::string GetDescription() override { return coffee_.GetDescription() + ", vanilla"; }
};







#endif //LEETCODE_DESIGN_PATTERN_H
