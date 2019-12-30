#ifndef OMNIPOTENTBRACES_H
#define OMNIPOTENTBRACES_H
//文件名的含义是无所不能的大括号
#include <iostream>
#include <atomic>
#include <vector>
using namespace std;

class Widget
{
public:
    Widget() {
        cout << __FUNCTION__ << "x: " << x << " y: " << y << endl;
    }
    Widget(int lx, double ly) : x{lx}, y{ly} {
        cout << __FUNCTION__ << "x: " << x << " y: " << y << endl;
    }
    Widget(std::initializer_list<long double> il) {
        cout << __FUNCTION__ << " Init By initializer_list" << endl;
        for (auto iter = il.begin(); iter != il.end(); iter++) {
            arr.push_back(*iter);
        }
    }
    void destory() { delete this; }
private:
    int x{100};
    atomic<double> y{10.0};
    vector<long double> arr;
    ~Widget() {
        cout << __FUNCTION__ << endl;
    }
};

void BracesTest() {
    /* 1、大括号几乎能适合所有的初始化工作，被作为统一的初始化*/
    int a{0};
    int b = {10};

    //这里用了一个小技巧，保证Widget只能在堆上分配，不能在栈上分配
    Widget* w = new Widget();
    w->destory();

    /* 2、唯一不适用的地方：
    *  如果构造函数中出现了具备std::initializer_list型别的行参，那么大括号初始化会非常强烈地优先选用带有该型别的重载版本
    *  只有实在找不到办法将大括号初始化物中的实参转换为std::initializer_list模板中的型别时，编译器才会退而去检查普通的重载决议
    */
    Widget* w1 = new Widget{10, 5.0};
    w1->destory();
    Widget* w2 = new Widget(10, 5.0);
    w2->destory();
}

#endif // OMNIPOTENTBRACES_H
