#ifndef PREFER_USING_OVER_TYPEDEF_H
#define PREFER_USING_OVER_TYPEDEF_H
#include <list>
#include <iostream>
/*
* 条款9：优先使用using而非typedef
* 原因： 在模板中，using具有压倒性的优势;
*       在非模板中，using也能更容易理解
*/

//1、模板
template<typename T>
using MyList1 = std::list<T>;


template<typename T>
struct MyList2 {
    typedef std::list<T> type;
};

template<typename T>
class MyClass1
{
public:
    MyClass1() {}
private:
    MyList1<T>          m_list1;            //而using一定代表某个型别，所以不用加typename
    typename MyList2<T>::type    m_list2;   //此处必须加上typename，否则编译器不知道type是型别还是成员
};

typedef void (*FP1)(int, long);
using FP2 = void (*)(int, long);    //可以看到using用起来含义更加清晰

void fp(int lhs, long rhs) {
    std::cout << __FUNCTION__ << std::endl;
}

void UsingTest() {
    MyList1<long>        list1;
    MyList2<long>::type  list2;
    MyClass1<long>       c1;

    FP1 funcPtr1 = &fp;
    FP2 funcPtr2 = &fp;
    funcPtr1(10, 100);
    funcPtr2(10, 100);
}

#endif // PREFER_USING_OVER_TYPEDEF_H
