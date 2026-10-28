// HRESULT AlphaShapeClass::Save(IStream *stream, BOOL clear_dirty) (0x0041F0C0, slot 6)
#include "shared/alpha_shape.hpp"
// @ref ??_7AlphaShapeClass@@6BIPersistStream@@@=0079bfd4
// @ref ??_7AlphaShapeClass@@6BIRTTITypeInfo@@@=0079bfb8
// @ref ??_7AlphaShapeClass@@6BINoticeSink@@@=0079bfb0
// @ref ??_7AlphaShapeClass@@6BINoticeSource@@@=0079bfa8
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall AlphaShapeClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = AbstractClass::Save(stream, clear_dirty);
    if (FAILED(result)) {
        return result;
    }
    return S_OK;
}
