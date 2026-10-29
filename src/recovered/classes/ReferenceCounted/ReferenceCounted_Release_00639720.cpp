// void ReferenceCounted::Release() (0x00639720)
// Drops one reference and deletes the object (through the scalar deleting destructor, slot 0) when none is left.
#include "shared/reference_counted.hpp"
void ReferenceCounted::Release()
{
    if (--RefCount == 0 && this != 0) {
        delete this;
    }
}
