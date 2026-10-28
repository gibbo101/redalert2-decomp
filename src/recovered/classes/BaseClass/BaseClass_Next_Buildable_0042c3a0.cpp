// BaseNodeClass *BaseClass::Next_Buildable(int type) (0x0042C3A0)
// The next node to build (of a type, -1 any), or null.
#include "shared/base.hpp"

BaseNodeClass *BaseClass::Next_Buildable(int type)
{
    int index = Next_Buildable_Index(type);
    if (index != -1) {
        return &Nodes[index];
    }
    return 0;
}
