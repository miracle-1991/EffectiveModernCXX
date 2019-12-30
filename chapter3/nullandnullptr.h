#ifndef NULLANDNULLPTR_H
#define NULLANDNULLPTR_H
#include <mutex>
#include <memory>
#include <iostream>
//本头文件用于描述条款8：优选选用nullptr，而非0或者NULL
//根本原因是nullptr具备指针型别，可以隐士转换为所有的裸指针型别。而NULL本质上是0,不具备指针型别
//二者的差异在模板型别推导中最为明显

using MuxGuard = std::lock_guard<std::mutex>;
template<typename FuncType, typename MuxType, typename PtrType>
auto lockAndCall(FuncType func, MuxType& mutex, PtrType ptr) -> decltype(func(ptr)) {
    MuxGuard g(mutex);
    return func(ptr);
}

class NWidget
{
public:
    NWidget() {}
};

int     f1(std::shared_ptr<NWidget> spw) { std::cout << __FUNCTION__ << std::endl; }
double  f2(std::unique_ptr<NWidget> upw) { std::cout << __FUNCTION__ << std::endl; }
bool    f3(NWidget* pw)                  { std::cout << __FUNCTION__ << std::endl; }

std::mutex f1m, f2m, f3m;

void NullptrTest() {
    //无法通过编译，0不能隐式转换为指针型别
//    auto r1 = lockAndCall(f1, f1m, 0);

    //无法通过编译，NULL不能隐士转换为指针型别
//    auto r2 = lockAndCall(f2, f2m, NULL);

    //可以通过编译，可以执行
    auto r3 = lockAndCall(f3, f3m, nullptr);
}

#endif // NULLANDNULLPTR_H
