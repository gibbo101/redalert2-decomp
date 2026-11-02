// void ReferenceCounted::Release() (0x00639720): deletes the object when the count drops to 0.
#include "shared/reference_counted.hpp"

void ReferenceCounted::Release()
{
    if (--RefCount == 0 && this != 0) {
        delete this;
    }
}
