// HRESULT __stdcall BombClass::Load(IStream *stream) (0x00436140): restores
// the bomb in place, restarts its sound object and swizzles the house, owner
// and target.
#include "shared/object.hpp"
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120
// @ref ??0AbstractClass@@QAE@ABVNoInitClass@@@Z=0040ff60
// @ref ?Init@UnknownAudioController@@QAEXXZ=00405bf0
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868

HRESULT __stdcall BombClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) BombClass(NoInitClass());
        unknown_3c.Init();
        unknown_54 = 0;
        SwizzleManager.Swizzle((void **)&unknown_28);
        SwizzleManager.Swizzle((void **)&Owner);
        SwizzleManager.Swizzle((void **)&Target);
    }
    return result;
}
