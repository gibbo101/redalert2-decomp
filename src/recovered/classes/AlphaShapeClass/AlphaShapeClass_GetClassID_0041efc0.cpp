// HRESULT AlphaShapeClass::GetClassID(GUID *clsid) (0x0041EFC0, slot 3)
#include "shared/alpha_shape.hpp"
// @ref ??_7AlphaShapeClass@@6BIPersistStream@@@=0079bfd4
// @ref ??_7AlphaShapeClass@@6BIRTTITypeInfo@@@=0079bfb8
// @ref ??_7AlphaShapeClass@@6BINoticeSink@@@=0079bfb0
// @ref ??_7AlphaShapeClass@@6BINoticeSource@@@=0079bfa8
// @ref _CLSID_AlphaShapeClass=007a1ee0

HRESULT __stdcall AlphaShapeClass::GetClassID(GUID *clsid)
{
    if (!clsid) {
        return E_POINTER;
    }
    *clsid = CLSID_AlphaShapeClass;
    return S_OK;
}
