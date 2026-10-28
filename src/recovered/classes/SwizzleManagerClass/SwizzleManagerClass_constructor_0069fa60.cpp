// SwizzleManagerClass::SwizzleManagerClass() (0x0069FA60)
// Both tables grow by 1000 entries.
#include "shared/swizzle.hpp"

SwizzleManagerClass::SwizzleManagerClass()
{
    UnswizzledPointers.Set_Growth_Step(1000);
    SwizzledPointers.Set_Growth_Step(1000);
}
