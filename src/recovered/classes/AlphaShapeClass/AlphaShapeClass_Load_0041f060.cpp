// HRESULT AlphaShapeClass::Load(IStream *stream) (0x0041F060, slot 5)
// The image is reloaded from the owner when drawn.
#include "shared/alpha_shape.hpp"
// @ref ??_7AlphaShapeClass@@6BIPersistStream@@@=0079bfd4
// @ref ??_7AlphaShapeClass@@6BIRTTITypeInfo@@@=0079bfb8
// @ref ??_7AlphaShapeClass@@6BINoticeSink@@@=0079bfb0
// @ref ??_7AlphaShapeClass@@6BINoticeSource@@@=0079bfa8
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868

HRESULT __stdcall AlphaShapeClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) AlphaShapeClass(NoInitClass());
        Swizzle_Pointer(Owner);
        Image = 0;
    }
    return result;
}
