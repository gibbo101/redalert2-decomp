// HRESULT __stdcall TechnoClass::Load(IStream *stream) (0x006D6850, slot 5)
// RadioClass::Load, then pointer fixups, the 0x00AC0BF8 list entry and the audio controller.
#include "shared/techno.hpp"
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868
// @ref ?Init@UnknownAudioController@@QAEXXZ=00405bf0
// @ref ?Load@RadioClass@@UAGJPAUIStream@@@Z=00636c60
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?unknown_abstracts_ac0bf8@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0bf8

HRESULT __stdcall TechnoClass::Load(IStream *stream)
{
    HRESULT result = RadioClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }
    unknown_408 = 0;
    SwizzleManager.Swizzle((void **)&House);
    for (int index = 0; index < 8; index++) {
        SwizzleManager.Swizzle((void **)&unknown_25c[index]);
    }
    SwizzleManager.Swizzle((void **)&unknown_1b0);
    SwizzleManager.Swizzle((void **)&unknown_3f8);
    SwizzleManager.Swizzle((void **)&unknown_228);
    SwizzleManager.Swizzle((void **)&unknown_22c);
    SwizzleManager.Swizzle((void **)&unknown_230);
    SwizzleManager.Swizzle((void **)&unknown_384);
    SwizzleManager.Swizzle((void **)&SpawnManager);
    SwizzleManager.Swizzle((void **)&unknown_234);
    SwizzleManager.Swizzle((void **)&unknown_23c);
    SwizzleManager.Swizzle((void **)&unknown_40c);
    SwizzleManager.Swizzle((void **)&unknown_410);
    SwizzleManager.Swizzle((void **)&unknown_208);
    SwizzleManager.Swizzle((void **)&unknown_20c);
    SwizzleManager.Swizzle((void **)&Cargo.Object);
    SwizzleManager.Swizzle((void **)&unknown_27c);
    if (unknown_108) {
        unknown_abstracts_ac0bf8.Delete(this);
        unknown_abstracts_ac0bf8.Add(this);
    }
    SwizzleManager.Swizzle((void **)&unknown_108);
    unknown_3d8.Init();
    unknown_3ec = 1;
    unknown_3f0 = 0;
    return S_OK;
}
