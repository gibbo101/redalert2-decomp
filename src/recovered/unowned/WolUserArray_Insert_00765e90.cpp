#include "shared/wol_sink.hpp"
bool WolUserArray::Insert_00765e90(WOL::User const &user, int index)
{
    if (index > Count) index = Count;
    if (index >= Capacity) Grow_00766e60();
    Grow_00766e60();
    if (index < Count) memmove(Items + index + 1, Items + index, (Count - index) * sizeof(WOL::User));
    new (Items + index) WOL::User(user);
    ++Count;
    return true;
}
