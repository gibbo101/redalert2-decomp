// void AlphaShapeClass::Detach(AbstractClass *target, bool all) (0x0041F0F0, slot 10)
#include "shared/alpha_shape.hpp"
// @ref ??_7AlphaShapeClass@@6BIPersistStream@@@=0079bfd4
// @ref ??_7AlphaShapeClass@@6BIRTTITypeInfo@@@=0079bfb8
// @ref ??_7AlphaShapeClass@@6BINoticeSink@@@=0079bfb0
// @ref ??_7AlphaShapeClass@@6BINoticeSource@@@=0079bfa8

void AlphaShapeClass::Detach(AbstractClass *target, bool all)
{
    if (target == (AbstractClass *)Owner) {
        unknown_3c = true;
    }
}
