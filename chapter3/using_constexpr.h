#ifndef USING_CONSTEXPR_H
#define USING_CONSTEXPR_H
#include <array>
namespace ConstExpr {

/*条款15：只要有可能使用constexpt，就尽可能地使用constexpr
 * constexpr主要有3个作用：
 * 1、用于修饰对象，该对象一定有const属性，并且由编译期已知的值完成初始化
 * 2、用于修饰函数接口，如果传入的实参值都是编译期已知的，则会在编译期产生结果，否则在运行期产生结果
 * 3、相比于不加constexpr的函数，constexpr函数可以用于更加广阔的语境中
 * 相当于define，但是又比define高级
*/

constexpr int pow(int base, int exp) {
    return exp == 0 ? 1 : base * pow(base, exp - 1);
    /*
     * 多于了一个可执行语句，无法通过编译
    int result = 1;
    for (int i = 0; i < exp; ++i) {
        result *= base;
    }
    return result;
    */
}

class Point
{
public:
    constexpr Point(double xVal = 0, double yVal = 0) : x(xVal), y(yVal) {}
    constexpr double xVal() const { return x; }
    constexpr double yVal() const { return y; }
private:
    double x, y;
};

constexpr Point midPoint(const Point& p1, const Point& p2) {
    return {(p1.xVal() + p2.xVal())/2, (p1.yVal() + p2.yVal())/2};
}

}

void ConstExprText() {
    //1、用于修饰编译期能确定其值的变量
    constexpr auto arrSize1 = 10;
    std::array<int, arrSize1> data1;

    int sz = 10;
    const auto arrSize2 = sz;
//    std::array<int, arrSize2> data2; //无法通过编译，arrSize2的值非编译期可知

    const auto numConds = 5;
    std::array<int, ConstExpr::pow(3, numConds)> results;

    constexpr ConstExpr::Point p1(9.4, 27.1);
    constexpr ConstExpr::Point p2(28.8, 5.3);
    constexpr auto mid = ConstExpr::midPoint(p1, p2);
}

#endif // USING_CONSTEXPR_H
