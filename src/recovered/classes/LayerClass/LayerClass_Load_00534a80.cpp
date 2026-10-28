// HRESULT LayerClass::Load(IStream *stream) (0x00534A80)
// Reads the object pointers back and registers each for swizzling.
#include "shared/layer.hpp"
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868

HRESULT LayerClass::Load(IStream *stream)
{
    if (!stream) {
        return E_POINTER;
    }
    int count = 0;
    HRESULT result = stream->Read(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return result;
    }
    for (int index = 0; index < count; index++) {
        ObjectClass *object;
        result = stream->Read(&object, sizeof(object), 0);
        if (FAILED(result)) {
            return result;
        }
        Add(object);
    }
    for (int i = 0; i < count; i++) {
        Swizzle_Pointer((*this)[i]);
    }
    return S_OK;
}
