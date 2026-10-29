#include "shared/wol_sink.hpp"
bool WolStringArray::Insert(Wstring const &text, int index)
{
    if (index > Count) index = Count;
    if (index >= Capacity) Grow();
    Grow();
    if (index < Count) memmove(Items + index + 1, Items + index, (Count - index) * sizeof(Wstring));
    new (Items + index) Wstring(text);
    ++Count;
    return true;
}
