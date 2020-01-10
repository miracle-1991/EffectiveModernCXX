#ifndef USING_OVERRIDE_H
#define USING_OVERRIDE_H
#include <vector>
#include <iostream>

namespace Terms12 {

using DataType = std::vector<double>;
class Base
{
public:
    virtual DataType& data() &  {}
    virtual DataType  data() && {}
};

class Widget : public Base
{
public:
    DataType& data() & override {
        std::cout << __FUNCTION__ << " LValue" << std::endl;
        return values;
    }

    DataType data() && override {
        std::cout << __FUNCTION__ << " RValue" << std::endl;
        return std::move(values);
    }

private:
    DataType values;
};

Widget makeWidger() {
    return Widget();
}

}

void OverrideTest() {
    Terms12::Widget w;
    auto w1 = w.data();
    auto w2 = Terms12::makeWidger().data();
}

#endif // USING_OVERRIDE_H
