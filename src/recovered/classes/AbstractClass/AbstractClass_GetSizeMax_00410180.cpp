// HRESULT __stdcall AbstractClass::GetSizeMax(ULARGE_INTEGER *size) (0x00410180)
// IPersistStream: Size_Of() plus the saved pointer.
#include "shared/abstract.hpp"

HRESULT __stdcall AbstractClass::GetSizeMax(ULARGE_INTEGER *size)
{
    if (size == 0) {
        return E_POINTER;
    }
    size->QuadPart = Size_Of() + sizeof(AbstractClass *);
    return S_OK;
}
