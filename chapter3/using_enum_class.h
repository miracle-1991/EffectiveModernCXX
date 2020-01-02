#ifndef USING_ENUM_CLASS_H
#define USING_ENUM_CLASS_H
#include <type_traits>
#include <iostream>
//条款10：优先使用带限定域的枚举类型
//原因：1、限定作用域的枚举型别仅在enum class作用域内可见，而enum却不行;
//     2、限定作用域的枚举型别只能通过强制型别转换才能转化成其他型别，而enum规定的型别却存在隐式转换
//     3、二者都支持底层型别指定，但是限定作用域的枚举型别默认底层型别是int，而enum没有默认的底层型别

enum class Color : std::uint64_t {
    White,
    Black,
    Blue,
    Orange
};

//提供一种enum class向其底层型别转化的工具
template<typename E>
constexpr typename std::underlying_type<E>::type toUType(E enumerator) noexcept  {
    return static_cast<typename std::underlying_type<E>::type>(enumerator);
}

void PrintEnum(std::uint64_t v) {
    std::cout << "Enum Value: " << v << std::endl;
}

void EnumClassTest() {
    Color c{Color::Blue};
    std::uint64_t nc = toUType(c);
    PrintEnum(nc);
}

#endif // USING_ENUM_CLASS_H
