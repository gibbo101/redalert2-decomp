#include "shared/wol_sink.hpp"
bool WolUserArray::Get(WOL::User &user, int index) const
{
    if (index >= 0 && index < Count) { user = Items[index]; return true; }
    return false;
}
