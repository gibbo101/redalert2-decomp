#include "shared/wol_channel_array_grow.hpp"
bool WolChannelArray::Insert_00766c20(WOL::Channel const &channel, int index)
{
    if (index > Count) index = Count;
    if (index >= Capacity) Grow_When_Full();
    Grow_When_Full();
    if (index < Count) memmove(Items + index + 1, Items + index, (Count - index) * sizeof(WOL::Channel));
    new (Items + index) WOL::Channel(channel);
    ++Count;
    return true;
}
