#include <iostream>
#include "omnipotentbraces.h"
#include "nullandnullptr.h"
#include "prefer_using_over_typedef.h"
#include "using_enum_class.h"
#include "using_delete_not_prive.h"
using namespace std;

int main(int argc, char *argv[])
{
    BracesTest();
    NullptrTest();
    UsingTest();
    EnumClassTest();
    DeleteTest();
    return 0;
}
