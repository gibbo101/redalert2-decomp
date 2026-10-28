// HRESULT __stdcall IsometricTileClass::Load(IStream *stream) (0x005280E0)
#include "shared/isometric_tile.hpp"
// @ref ?Load@ObjectClass@@UAGJPAUIStream@@@Z=005d4760
// @ref ??0ObjectClass@@QAE@ABVNoInitClass@@@Z=005d2500
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868

HRESULT __stdcall IsometricTileClass::Load(IStream *stream)
{
    HRESULT result = ObjectClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) IsometricTileClass(NoInitClass());
        SwizzleManager.Swizzle((void **)&Type);
    }
    return result;
}
