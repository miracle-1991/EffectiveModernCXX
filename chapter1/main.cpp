#include <iostream>
#include <vector>
#include "cp1.h"
using namespace std;

//情况1:ParamType是个指针或者引用，但不是万能引用
void Func1Test() {
    int x = 100;
    func1(x);   //输出int&

    const int cx = x;
    func1(cx);  //输出int const&

    const int& rx = x;
    func1(rx);  //输出int const&

    func1(&x);  //输出int*

    const int *px = &x;
    func1(px);  //输出int const*

    //边缘情形
    const char name[] = "J.P.Bridge";
    func1(name);    //输出char const*。其实本来有两种匹配，一种发生了退化，一种没有退化，只不过退化的那个更匹配
}

//情况2:ParamType是个万能引用
void Func2Test() {
    int x = 100;
    func2(x);   //输出int&

    const int cx = x;
    func2(cx);  //输出int const&

    const int& rx = x;
    func2(rx);  //输出int const&

    func2(100); //输出int&&

    //边缘情形
    const char name[] = "J.P.Bridge";
    func2(name);    //输出char const (&) [11]，没有发生退化
}

//情况3:ParamType既非指针又非引用
void Func3Test() {
    int x = 100;
    func3(x);   //输出int

    const int cx = x;
    func3(cx);  //输出int

    const int& rx = x;
    func3(rx);  //输出int

    const char* const ptr = "Fun with pointers";
    func3(ptr); //输出char const*

    //边缘情形
    const char name[] = "J.P.Bridge";
    func3(name);    //数组退化到指针,输出char const*
}

void AutoTest() {
    //auto的型别推导大部分情况下与模板型别推导一模一样，唯有一处不同
    auto x = {1,2,3,4};
    cout << __FUNCTION__ << " param type: " << type_id_with_cvr<decltype (x)>().pretty_name() << endl;
    //输出:std::initializer_list<int>
    //auto会假定大括号初始化表达式代表一个std::inittializer<T>,而模板型别推导却不会

    //auto型别推导也有不适用的地方，比如
    vector<bool> flag{true, false, false, true, true, false};
    auto item1 = flag[1];
    cout << __FUNCTION__ << " item1 type: " << type_id_with_cvr<decltype (item1)>().pretty_name() << endl;
    //"隐形"的代理型别可以导致auto根据初始化表达式推导出错误的型别。此处，本应该是bool型，由于隐形代理operator[]的存在，得到了std::_Bit_reference
    //而这个reference在bool item = flag[1]的时候会自动隐式型别转换为bool
    //遇到这种代理类时应该使用显式的型别转换,如下：
    auto item2 = static_cast<bool>(flag[1]);
    cout << __FUNCTION__ << " item2 type: " << type_id_with_cvr<decltype (item2)>().pretty_name() << endl;
}

void DecltypeTest() {
    //decltype的几个用法
    //1、起到与auto类似的作用，但与auto的用法不一样：auto在初始化时进行型别推导，而decltype总是以一个表达式作为参数
    int i = 10;
    decltype(i) j;

    //2、主要用途：声明那些返回值依赖于行参型别的函数模板
    vector<int> arr{0,1,2,3,4,5,6};
    GetItem(arr, 3)++;  //decltype得到了arr[3]的引用
    cout << arr[3] << endl;
}

int main()
{
    //模板型别推导
    Func1Test();
    Func2Test();
    Func3Test();

    //auto型别推导
    AutoTest();

    //decltype用法
    DecltypeTest();
    return 0;
}
