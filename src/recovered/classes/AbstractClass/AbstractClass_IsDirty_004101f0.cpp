// HRESULT __stdcall AbstractClass::IsDirty() (0x004101F0)
// IPersistStream: S_OK when changed since the last clearing save, else S_FALSE.
#include "shared/abstract.hpp"

HRESULT __stdcall AbstractClass::IsDirty()
{
    return !Dirty;
}
