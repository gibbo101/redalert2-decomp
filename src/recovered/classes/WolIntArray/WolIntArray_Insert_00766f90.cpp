#include "shared/wol_sink.hpp"
bool WolIntArray::Insert_00766f90(int const &value, int index)
{
    if (index > Count) index = Count;
    if (index >= Capacity) Grow();
    Grow();
    if (index < Count) memmove(Items + index + 1, Items + index, (Count - index) * sizeof(int));
    new (Items + index) int(value);
    ++Count;
    return true;
}
