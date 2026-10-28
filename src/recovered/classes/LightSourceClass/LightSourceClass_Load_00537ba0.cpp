// HRESULT __stdcall LightSourceClass::Load(IStream *stream) (0x00537BA0):
// restores the light in place.
#include "shared/light_source.hpp"
// @ref ??_7LightSourceClass@@6BIPersistStream@@@=007a5560
// @ref ??_7LightSourceClass@@6BIRTTITypeInfo@@@=007a5544
// @ref ??_7LightSourceClass@@6BINoticeSink@@@=007a553c
// @ref ??_7LightSourceClass@@6BINoticeSource@@@=007a5534
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120
// @ref ??0AbstractClass@@QAE@ABVNoInitClass@@@Z=0040ff60

HRESULT __stdcall LightSourceClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) LightSourceClass(NoInitClass());
        result = S_OK;
    }
    return result;
}
