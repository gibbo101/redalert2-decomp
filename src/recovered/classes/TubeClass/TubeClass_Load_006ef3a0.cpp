// HRESULT __stdcall TubeClass::Load(IStream *stream) (0x006EF3A0)
// Restores the tube in place.
#include "shared/tube.hpp"
#include "shared/vector_class.hpp"
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120
// @ref ??0AbstractClass@@QAE@XZ=0040ff10
// @ref ??_7TubeClass@@6BIPersistStream@@@=007adb38
// @ref ??_7TubeClass@@6BIRTTITypeInfo@@@=007adb1c
// @ref ??_7TubeClass@@6BINoticeSink@@@=007adb14
// @ref ??_7TubeClass@@6BINoticeSource@@@=007adb0c

HRESULT __stdcall TubeClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) TubeClass(NoInitClass());
        result = S_OK;
    }
    return result;
}
