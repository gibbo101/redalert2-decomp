// void TagClass::unknown_func_6b3cc0() (0x006B3CC0)
// Marks the tag and queues it in the abstract list 0x00AC0CD8.
#include "shared/object.hpp"

void TagClass::unknown_func_6b3cc0()
{
    unknown_34 = true;
    unknown_objects_ac0cd8.Add((ObjectClass *)this);
}
