#include "test_design_pattern.h"
#include "../Concepts/design_pattern.h"
#include <iostream>
#include <cassert>

//void test_simple_factory()
//{
//    IDoor* door = DoorFactory::MakeDoor(100, 200);
//    std::cout << "Width: " << door->GetWidth() << std::endl;
//    std::cout << "Height: " << door->GetHeight() << std::endl;
//}


void test_normal_factory()
{
    HiringManager* devManager = new OtherManager<Developer>();
    devManager->takeInterview();

    HiringManager* marketingManager = new OtherManager<CommunityExecutive>();
    marketingManager->takeInterview();
}


void test_abstract_factory()
{
    IDoorFactory* woodenFactory = new DoorFactory<WoodenDoor, Carpenter>();
    {
        IDoor* door = woodenFactory->MakeDoor();
        IDoorFittingExpert* expert = woodenFactory->MakeFittingExpert();
        door->GetDescription();
        expert->GetDescription();
    }

    IDoorFactory* ironFactory = new DoorFactory<IronDoor, Welder>();
    {
        IDoor* door = ironFactory->MakeDoor();
        IDoorFittingExpert* expert = ironFactory->MakeFittingExpert();
        door->GetDescription();
        expert->GetDescription();
    }
}

// 生成者
void test_generate()
{
    Burger* burger = Burger::BurgerBuilder(14).AddPepperoni().AddLettuce().AddTomato().Build();
    burger->showFlavors();
}

// 适配器
void test_adapter()
{
    WildDog dog;
    WildDogAdapter dogAdapter(dog);

    Hunter hunter;
    hunter.Hunt(dogAdapter);
}

// 观察者 定义对象间的依赖关系, 以至于一个对象的状态改变, 依赖它的对象们都会收到通知.
void test_observer()
{
    JobSeeker johnDoe("John Doe");
    JobSeeker janeDoe("Jane Doe");

    JobPostings jobPostings;
    jobPostings.Attach(johnDoe);
    jobPostings.Attach(janeDoe);

    jobPostings.AddJob(JobPost("Software Engineer"));
}

// 访问者 访问者模式允许你为对象们增加更多的操作, 却不必修改它们.
void test_visitor()
{
    Monkey monkey;
    Lion lion;
    Dolphin dolphin;
    // 相当于以同样的接口 调用不同动物的行为
    Speak speak;
    monkey.Accept(speak);
    lion.Accept(speak);
    dolphin.Accept(speak);
}

void test_singleton()
{
    // 因为构造函数 =delete了 所以只能用引用的形式
    const President& president1 = President::GetInstance();
    const President& president2 = President::GetInstance();

    assert(&president1 == &president2); // same address, point to same object.
}

void test_bridge()
{
    DarkTheme darkTheme;
    About about(darkTheme);
    Careers careers(darkTheme);

    std::cout << about.GetContent() << std::endl;
    std::cout << careers.GetContent() << std::endl;
}

// 组合模式在我看来甚至称不上什么模式, 其核心就是多态特性的体现.
// 另一个核心在于, 容器存储的是接口类型, 利用多态, 可以迭代处理通用操作.
void test_compisite()
{
    mDeveloper john("John Doe", 12000);
    Designer jane("Jane Doe", 15000);

    Organization org;
    org.AddEmployee(john);
    org.AddEmployee(jane);

    std::cout << "Net salaries: " << org.GetNetSalaries() << std::endl;
}

// 装饰模式的形态很有意思, 像是静态语言的动态化. 其实实现上与组合模式类似, 但关键之处在于, 其依赖的对象是其父类接口.
// 顾名思义, 装饰模式, 装饰的是对象自身, 且支持重复装饰. 譬如上述实例中, 完全可以加两遍牛奶. 但最终要保证接口的一致性,
// 就像你的房子无论装饰成什么样子, 它依然只是你的房子.
void test_decorator()
{
    ICoffee* someCoffee = new SimpleCoffee();
    std::cout << someCoffee->GetCost() << std::endl;
    std::cout << someCoffee->GetDescription() << std::endl;

    someCoffee = new MilkCoffee(*someCoffee);
    std::cout << someCoffee->GetCost() << std::endl;
    std::cout << someCoffee->GetDescription() << std::endl;

    someCoffee = new WhipCoffee(*someCoffee);
    std::cout << someCoffee->GetCost() << std::endl;
    std::cout << someCoffee->GetDescription() << std::endl;

    someCoffee = new VanillaCoffee(*someCoffee);
    std::cout << someCoffee->GetCost() << std::endl;
    std::cout << someCoffee->GetDescription() << std::endl;
}