// int __stdcall AbstractClass::What_Am_I() (0x0040FFB0)
// IRTTITypeInfo: the object kind (Kind_Of); `this` is the +4 interface.
#include "shared/abstract.hpp"

int __stdcall AbstractClass::What_Am_I()
{
    return Kind_Of();
}
