// HRESULT __stdcall InfantryTypeClass::Load(IStream *stream) (0x0050AB40)
// Frees the sequence table, loads the techno type, restores the type in
// place, reloads its images, rebuilds the comment voice and death
// animation lists (swizzling the animations) and reads a fresh sequence
// table (38 entries).
#include "shared/infantry_type.hpp"
// @ref ??0?$TypeList@H@@QAE@ABVNoInitClass@@@Z=0050b0f0
// @ref ??0?$TypeList@PAVAnimTypeClass@@@@QAE@ABVNoInitClass@@@Z=0050b100
// @ref ??_7?$DynamicVectorClass@PAVAnimTypeClass@@@@6B@=007a3b7c
// @ref ??_G?$DynamicVectorClass@PAVAnimTypeClass@@@@UAEPAXI@Z=0050b260
// @ref ??_7?$DynamicVectorClass@H@@6B@=0079da94
// @ref ??_G?$DynamicVectorClass@H@@UAEPAXI@Z=0046cf50
// @ref ?Load@TechnoTypeClass@@UAGJPAUIStream@@@Z=006de260
// @ref ??0TechnoTypeClass@@QAE@ABVNoInitClass@@@Z=006da6e0
// @ref ?unknown_func_5d6730@ObjectTypeClass@@QAEXXZ=005d6730
// @ref ?unknown_func_5d7630@ObjectTypeClass@@QAEXXZ=005d7630
// @ref ?Swizzle@SwizzleManagerClass@@QAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868
// @ref ??0?$DynamicVectorClass@PAVAnimTypeClass@@@@QAE@IPBQAVAnimTypeClass@@@Z=0050b480
// @ref ?Add@?$DynamicVectorClass@PAVAnimTypeClass@@@@QAE_NABQAVAnimTypeClass@@@Z=0050b590
// @ref ??0?$DynamicVectorClass@H@@QAE@IPBH@Z=0046d1f0
// @ref ?Add@?$DynamicVectorClass@H@@QAE_NABH@Z=0046d300
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b

// Rebuilds a list in place from its saved count and elements.
template <class T>
static inline void Load_List(IStream *stream, TypeList<T> &list)
{
    new (&list) TypeList<T>;
    int count;
    stream->Read(&count, sizeof(count), 0);
    for (int index = 0; index < count; index++) {
        T value;
        stream->Read(&value, sizeof(value), 0);
        list.Add(value);
    }
}

HRESULT __stdcall InfantryTypeClass::Load(IStream *stream)
{
    if (DoControls != 0) {
        operator delete(DoControls);
        DoControls = 0;
    }
    HRESULT result = TechnoTypeClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) InfantryTypeClass(NoInitClass());
        unknown_func_5d6730();
        unknown_func_5d7630();
        Load_List(stream, VoiceComment);
        Load_List(stream, DeadBodies);
        int index;
        for (index = 0; index < DeadBodies.Count(); index++) {
            Swizzle_Pointer(DeadBodies[index]);
        }
        Load_List(stream, DeathAnims);
        for (index = 0; index < DeathAnims.Count(); index++) {
            Swizzle_Pointer(DeathAnims[index]);
        }
        DoControls = (DoInfoStruct *)operator new(38 * sizeof(DoInfoStruct));
        stream->Read(DoControls, 38 * sizeof(DoInfoStruct), 0);
    }
    return result;
}
