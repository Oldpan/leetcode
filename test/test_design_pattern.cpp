#include "test_design_pattern.h"
#include "../Concepts/design_pattern.h"
#include <iostream>

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