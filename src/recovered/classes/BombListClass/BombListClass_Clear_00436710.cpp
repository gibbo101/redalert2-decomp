// void BombListClass::Clear() (0x00436710): empties both lists, keeping
// their allocated sizes, and resets +0x30 to 45.
#include "shared/object.hpp"

void BombListClass::Clear()
{
    int length = Bombs.Length();
    unknown_30 = 45;
    Bombs.Clear();
    Bombs.Resize(length);
    DynamicVectorClass<TechnoClass *> &list = unknown_18;
    length = list.Length();
    list.Clear();
    list.Resize(length);
}
