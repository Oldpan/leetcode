//
// Created by prototype on 2019/9/14.
//

#include <stdio.h>
#include <stdlib.h>
#include "c_polymorphism.h"


// 使用C语言实现多态

typedef void (*fptrSet)(void*,int);
typedef int (*fptrGet)(void*);
typedef void (*fptrDisplay)();

typedef struct _functions {
    // 函数
    fptrSet setX;
    fptrGet getX;
    fptrSet setY;
    fptrGet getY;
    fptrDisplay display;

} vFunctions;

typedef struct _shape {
    vFunctions functions;
    // 基类变量
    int x;
    int y;
} Shape;

void shapeDisplay(Shape *shape) { printf("Shape\n");}
void shapeSetX(Shape *shape, int x) {shape->x = x;}
void shapeSetY(Shape *shape, int y) {shape->y = y;}
int shapeGetX(Shape *shape) { return shape->x;}
int shapeGetY(Shape *shape) { return shape->y;}

Shape* getShapeInstance() {
    Shape *shape = (Shape*)malloc(sizeof(Shape));
    shape->functions.display = (fptrDisplay)shapeDisplay;
    shape->functions.setX = (fptrSet)shapeSetX;
    shape->functions.getX = (fptrGet)shapeGetX;
    shape->functions.setY = (fptrSet)shapeSetY;
    shape->functions.getY = (fptrGet)shapeGetY;
    shape->x = 100;
    shape->y = 100;
    return shape;
}

typedef struct _rectangle {
    Shape base;
    int width;
    int height;
} Rectangle;

void rectangleSetX(Rectangle *rectangle, int x) { rectangle->base.x = x;}
void rectangleSetY(Rectangle *rectangle, int y) { rectangle->base.y;}
int rectangleGetX(Rectangle *rectangle) { return rectangle->base.x;}
int rectangleGetY(Rectangle *rectangle) { return rectangle->base.y;}
void rectangleDisplay() { printf("Rectangle\n");}

Rectangle* getRectangleInstance() {
    Rectangle *rectangle = (Rectangle*)malloc(sizeof(Rectangle));
    rectangle->base.functions.display = (fptrDisplay)rectangleDisplay;
    rectangle->base.functions.setX = (fptrSet)rectangleSetX;
    rectangle->base.functions.getX = (fptrGet)rectangleGetX;
    rectangle->base.functions.setY = (fptrSet)rectangleSetY;
    rectangle->base.functions.getY = (fptrGet)rectangleGetY;
    rectangle->base.x = 200;
    rectangle->base.y = 200;
    rectangle->height = 300;
    rectangle->width = 500;
    return rectangle;
}





// 虚函数表结构
typedef struct _base_vtbl
{
    void(*dance)(void *);   // 指向void* 参数类型　void类型的函数指针
    void(*jump)(void *);
} base_vtbl;

//基类
typedef struct
{
    /*virtual table*/
    base_vtbl *vptr;  // 这个指针指向虚函数表
}base;

void base_dance(void *temp)
{
    printf("base dance\n");
}

void base_jump(void *temp)
{
printf("base jump\n");
}

/* global vtable for base */
base_vtbl base_table =
{
        base_dance,
        base_jump
};       // 初始化虚函数表的指针　指向两个基类的函数

// 基类的构造函数
base * new_base()
{
    base *temp = (base *)malloc(sizeof(base));
    temp->vptr = &base_table;
    return temp;
}


//派生类
typedef struct
{
    base super;  // 派生类里面有基类　注意顺序不能变
    /*derived members */
    int high;
}derived1;

void derived1_dance(void * temp)
{
    /*implementation of derived1's dance function */
    printf("derived1 dance\n");
}

void derived1_jump(void * ttemp)
{
    /*implementation of derived1's jump function */
    derived1* temp = (derived1 *)ttemp;
    printf("derived1 jump:%d\n", temp->high);
}

/*global vtable for derived1 */
base_vtbl derived1_table =
{
        derived1_dance,
        derived1_jump
};

//派生类的构造函数
derived1 * new_derived1(int h)
{
    derived1 * temp= (derived1 *)malloc(sizeof(derived1));
    temp->super.vptr = &derived1_table;
    temp->high = h;
    return temp;
}




void test_poly_c()
{
    // Shape 的用例
    printf("----Test Shape:----\n");
    Shape *sptr = getShapeInstance();
    sptr->functions.setX(sptr,35);
    sptr->functions.display();
    printf("%d\n", sptr->functions.getX(sptr));

    // 输出测试

    printf("&sptr:0x%p sptr:0x%p *sptr:0x%p\n", &sptr, sptr, *sptr);
    printf("&shapeSetX:0x%p shapeSetX:0x%p\n", &shapeSetX, shapeSetX);
    printf("&shapeGetX:0x%p shapeGetX:0x%p\n", &shapeGetX, shapeGetX);
    printf("&shapeSetY:0x%p shapeSetY:0x%p\n", &shapeSetY, shapeSetY);
    printf("&shapeGetY:0x%p shapeGetY:0x%p\n", &shapeGetY, shapeGetY);

    printf("&sptr->functions:0x%p \n",&(sptr->functions));
    printf("sptr->functions:0x%p \n",sptr->functions);


    printf("&sptr->functions.setX:0x%p sptr->functions.setX:0x%p shapeSetX:0x%p\n"
        , &(sptr->functions.setX), sptr->functions.setX, shapeSetX);

    printf("&sptr->functions.getX:0x%p sptr->functions.getX:0x%p shapeGetX:0x%p\n"
        , &(sptr->functions.getX), sptr->functions.getX, shapeGetX);

    printf("&sptr->functions.setY:0x%p sptr->functions.setY:0x%p shapeSetY:0x%p\n"
        , &(sptr->functions.setY), sptr->functions.setY, shapeSetY);

    printf("&sptr->functions.getY:0x%p sptr->functions.getY:0x%p shapeGetY:0x%p\n"
        , &(sptr->functions.getY), sptr->functions.getY, shapeGetY);

    printf("&sptr->functions.display:0x%p sptr->functions.display:0x%p shapeDisplay:0x%p\n"
        , &(sptr->functions.display), sptr->functions.display, shapeDisplay);

    printf("&sptr->x:0x%p sptr->x:%d\n", &(sptr->x), sptr->x);
    printf("&sptr->y:0x%p sptr->y:%d\n", &(sptr->y), sptr->y);


    // Rectangle 用例
    printf("----Test Rectangle:----\n");
    Rectangle *rptr = getRectangleInstance();
    rptr->base.functions.setX(rptr,35);
    rptr->base.functions.display();
    printf("%d\n", rptr->base.functions.getX(rptr));


    // 测试多态
    printf("----Test Polymorphism:----\n");
    Shape *shapes[3];

    shapes[0] = getShapeInstance();
    shapes[0]->functions.setX(shapes[0],1);

    shapes[1] = (Shape *)getRectangleInstance();
    shapes[1]->functions.setX(shapes[1],2);

    shapes[2] = getShapeInstance();
    shapes[2]->functions.setX(shapes[2],3);

    for(int i=0; i<3; i++) {
        shapes[i]->functions.display();
        printf("%d\n", shapes[i]->functions.getX(shapes[i]));
    }

}


void test_poly_c_2()
{
    base * bas = new_base();
    //这里调用的是基类的成员函数
    bas->vptr->dance((void *)bas);
    bas->vptr->jump((void *)bas);

    derived1 * child = new_derived1(100);
    //基类指针指向派生类
    bas = (base *)child;

    //这里调用的其实是派生类的成员函数
    bas->vptr->dance((void *)bas);
    bas->vptr->jump((void *)bas);

}