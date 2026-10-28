// HRESULT LayerClass::Save(IStream *stream) (0x00534A10)
// The object count, then each object pointer.
#include "shared/layer.hpp"

HRESULT LayerClass::Save(IStream *stream)
{
    if (!stream) {
        return E_POINTER;
    }
    int count = Count();
    HRESULT result = stream->Write(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return result;
    }
    for (int index = 0; index < count; index++) {
        result = stream->Write(&(*this)[index], sizeof(ObjectClass *), 0);
        if (FAILED(result)) {
            return result;
        }
    }
    return S_OK;
}
