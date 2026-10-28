// HRESULT __stdcall WarheadTypeClass::Load(IStream *stream) (0x00720DB0)
// Restores the warhead in place, rebuilds its animation list from the saved
// count and entries, and swizzles the list and the particle system.
#include "shared/warhead_type.hpp"
// @ref ??_7?$DynamicVectorClass@PAVAnimTypeClass@@@@6B@=007a3b7c
// @ref ??_G?$DynamicVectorClass@PAVAnimTypeClass@@@@UAEPAXI@Z=0050b260
// @ref ??_7?$DynamicVectorClass@H@@6B@=0079da94
// @ref ??_G?$DynamicVectorClass@H@@UAEPAXI@Z=0046cf50
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868
// @ref ??0?$DynamicVectorClass@PAVAnimTypeClass@@@@QAE@IPBQAVAnimTypeClass@@@Z=0050b480
// @ref ?Add@?$DynamicVectorClass@PAVAnimTypeClass@@@@QAE_NABQAVAnimTypeClass@@@Z=0050b590
// @ref ??0?$VectorClass@PAVAnimTypeClass@@@@QAE@IPBQAVAnimTypeClass@@@Z=0050b860

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

HRESULT __stdcall WarheadTypeClass::Load(IStream *stream)
{
    HRESULT result = AbstractTypeClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }
    new (this) WarheadTypeClass(NoInitClass());
    Load_List(stream, AnimList);
    for (int index = 0; index < AnimList.Count(); index++) {
        Swizzle_Pointer(AnimList[index]);
    }
    Swizzle_Pointer(Particle);
    return S_OK;
}
