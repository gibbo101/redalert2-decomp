#include "shared/wol_sink.hpp"
bool WolIntArray::Remove_007681a0(int index)
{
    if (Count == 0) return false;
    if (index < 0) index = 0;
    if (index >= Count) index = Count - 1;
    memmove(Items + index, Items + index + 1, (Count - (index + 1)) * sizeof(int));
    --Count;
    Shrink();
    return true;
}
