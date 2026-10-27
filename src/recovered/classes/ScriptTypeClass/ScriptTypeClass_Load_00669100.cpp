// HRESULT __stdcall ScriptTypeClass::Load(IStream *stream) (0x00669100)
// Restores the type in place.
#include "shared/script.hpp"
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120
// @ref ??0AbstractTypeClass@@QAE@ABVNoInitClass@@@Z=004106e0

HRESULT __stdcall ScriptTypeClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) ScriptTypeClass(NoInitClass());
        result = S_OK;
    }
    return result;
}

