#ifndef CP1_H
#define CP1_H
#include <iostream>
#include <boost/type_index.hpp>

using namespace std;
using boost::typeindex::type_id_with_cvr;

//情况1:ParamType是个指针或者引用，但不是万能引用
template <typename T>
void func1(T& param) {
    cout << __FUNCTION__ << " param type: " << type_id_with_cvr<decltype (param)>().pretty_name() << endl;
}

template <typename T>
void func1(T* param) {
    cout << __FUNCTION__ << " param type: " << type_id_with_cvr<decltype (param)>().pretty_name() << endl;
}

//情况2:ParamType是个万能引用
template <typename T>
void func2(T&& param) {
    cout << __FUNCTION__ << " param type: " << type_id_with_cvr<decltype (param)>().pretty_name() << endl;
}

//情况3:ParamType既非指针又非引用
template <typename T>
void func3(T param) {
    cout << __FUNCTION__ << " param type: " << type_id_with_cvr<decltype (param)>().pretty_name() << endl;
}

//decltype推到函数的返回值型别
template <typename Container, typename Index>
auto GetItem(Container& c, Index i) -> decltype(c[i]) {
    return c[i];
}

#endif // CP1_H
