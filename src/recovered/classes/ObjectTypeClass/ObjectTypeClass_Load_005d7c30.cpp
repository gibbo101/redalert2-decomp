// HRESULT __stdcall ObjectTypeClass::Load(IStream *stream) (0x005D7C30)
// Drops the cached buffers and voxel pairs, loads the base, then rebuilds
// the cleared members and looks the alternate image up in the mixfiles.
#include "shared/object_type.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120
// @ref ??1UnknownPairFirst@@QAE@XZ=007190c0
// @ref ??1UnknownPairSecond@@QAE@XZ=0059eba0
// @ref ??1UnknownBuffer@@QAE@XZ=005d8070
// @ref ?unknown_func_5d66a0@ObjectTypeClass@@QAEXXZ=005d66a0
// @ref ??3@YAXPAX@Z=00781d3b
// @ref __makepath=007831f0
// @ref ?Retrieve@?$MixFileClass@VCCFileClass@@@@SIPBXPBD@Z=005956c0
// @ref ??_C@_04BOIE@?4SHP?$AA@=007ced14

extern "C" void __cdecl _makepath(char *path, char const *drive, char const *dir, char const *fname, char const *ext);

// Empties a pair without freeing (the loaded pointers are stale). Used
// for unknown_b0 and unknown_b8 only: that inline-site count is what keeps
// exactly the first buffer destructor inline (one more or one fewer site
// changes which ones VC6 expands).
static inline void Clear_Pair(UnknownObjectPair &pair)
{
    pair.unknown_00 = 0;
    pair.unknown_04 = 0;
}

HRESULT __stdcall ObjectTypeClass::Load(IStream *stream)
{
    unknown_214.~UnknownBuffer();
    unknown_228.~UnknownBuffer();
    unknown_23c.~UnknownBuffer();
    unknown_250.~UnknownBuffer();
    delete unknown_b0.unknown_00;
    unknown_b0.unknown_00 = 0;
    delete unknown_b0.unknown_04;
    unknown_b0.unknown_04 = 0;
    delete unknown_b8.unknown_00;
    unknown_b8.unknown_00 = 0;
    delete unknown_b8.unknown_04;
    unknown_b8.unknown_04 = 0;
    delete unknown_c0.unknown_00;
    unknown_c0.unknown_00 = 0;
    delete unknown_c0.unknown_04;
    unknown_c0.unknown_04 = 0;
    unknown_func_5d66a0();

    HRESULT result = AbstractClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }

    unknown_a4 = 0;
    unknown_a8 = false;
    unknown_ac = 0;
    new (&unknown_214) UnknownBuffer;
    new (&unknown_228) UnknownBuffer;
    new (&unknown_23c) UnknownBuffer;
    new (&unknown_250) UnknownBuffer;
    Clear_Pair(unknown_b0);
    Clear_Pair(unknown_b8);
    unknown_c0.unknown_00 = 0;
    unknown_c0.unknown_04 = 0;
    for (int index = 0; index < 15; index++) {
        unknown_c8[index].unknown_00 = 0;
        unknown_c8[index].unknown_04 = 0;
        unknown_140[index].unknown_00 = 0;
        unknown_140[index].unknown_04 = 0;
    }
    if (unknown_1e3.Buffer[0] != 0) {
        char filename[260];
        _makepath(filename, 0, 0, unknown_1e3.Buffer, ".SHP");
        unknown_ac = (int)MixFileClass<CCFileClass>::Retrieve(filename);
    }
    return S_OK;
}
