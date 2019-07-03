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

void test_generate()
{
    Burger* burger = Burger::BurgerBuilder(14).AddPepperoni().AddLettuce().AddTomato().Build();
    burger->showFlavors();
}


void test_adapter()
{
    WildDog dog;
    WildDogAdapter dogAdapter(dog);

    Hunter hunter;
    hunter.Hunt(dogAdapter);
}

