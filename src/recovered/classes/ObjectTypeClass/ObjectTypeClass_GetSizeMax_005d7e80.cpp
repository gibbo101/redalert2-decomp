// HRESULT __stdcall ObjectTypeClass::GetSizeMax(ULARGE_INTEGER *size) (0x005D7E80)
#include "shared/object_type.hpp"
// @ref ?GetSizeMax@AbstractClass@@UAGJPATULARGE_INTEGER@@@Z=00410180

HRESULT __stdcall ObjectTypeClass::GetSizeMax(ULARGE_INTEGER *size)
{
    HRESULT result = AbstractClass::GetSizeMax(size);
    if (SUCCEEDED(result)) {
        result = S_OK;
    }
    return result;
}
