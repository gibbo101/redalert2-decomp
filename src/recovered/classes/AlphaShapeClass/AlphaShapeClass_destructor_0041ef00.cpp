// AlphaShapeClass::~AlphaShapeClass() (0x0041EF00)
// Leaves both lists.
#include "shared/alpha_shape.hpp"
#include "shared/object_lists.hpp"
// @ref ??_7AlphaShapeClass@@6BIPersistStream@@@=0079bfd4
// @ref ??_7AlphaShapeClass@@6BIRTTITypeInfo@@@=0079bfb8
// @ref ??_7AlphaShapeClass@@6BINoticeSink@@@=0079bfb0
// @ref ??_7AlphaShapeClass@@6BINoticeSource@@@=0079bfa8
// @ref ??1AbstractClass@@UAE@XZ=0040ff90

AlphaShapeClass::~AlphaShapeClass()
{
    unknown_AlphaShapeClass_list_0083c648.Delete(this);
    unknown_objects_ac0d60.Delete((ObjectClass *)this);
}
