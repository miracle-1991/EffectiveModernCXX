#ifndef USING_DELETE_NOT_PRIVE_H
#define USING_DELETE_NOT_PRIVE_H
#include <string>
#include <iostream>
/*
* 条款11：优先使用delete而非private
* 原因：将成员函数声明为private其实就是模拟的delete这种行为，当然没有本尊好使
* delete的几种用法如下:
*/

//1、禁止拷贝（包括拷贝内构造和拷贝赋值）
class NotCopyable
{
public:
    NotCopyable() = default;
    NotCopyable(const NotCopyable& rhs) = delete;
    NotCopyable& operator = (const NotCopyable& rhs) = delete;
};

class MyName : public NotCopyable
{
public:
    explicit MyName(std::string nm) : m_nm(nm) {}
private:
    std::string m_nm;
};

//2、禁止不想要的模板具现
template<typename T>
void processPointer(T* ptr) {
    std::cout << __FUNCTION__ << " T addr: " << &ptr << std::endl;
}

template<>
void processPointer<void>(void* ptr) = delete;

void DeleteTest() {
    MyName nm1("jixiaolong");
//    MyName nm2 = nm1; //编译不通过
    MyName nm2("jiji");
//    nm2 = nm1;        //编译不通过

    char* nm3 = new char[100];
    processPointer(nm3);
    void* nm4 = static_cast<void*>(nm3);
//    processPointer(nm4);  //编译不通过
    delete[] nm3;
}

#endif // USING_DELETE_NOT_PRIVE_H
