// HRESULT __stdcall FootClass::Load(IStream *stream) (0x004C9D10)
// Releases the locomotor, loads the techno, rebuilds and reloads the two
// AbstractClass vectors (count, then each pointer), loads the locomotor
// (OleLoadFromStream) and requests the pointer fix-ups.
#include "shared/foot.hpp"
#include "shared/parasite.hpp"
#include "shared/win32_api.hpp"
// @ref ?Load@TechnoClass@@UAGJPAUIStream@@@Z=006d6850
// @ref __imp__OleLoadFromStream@12=0079a5ec
// @ref _IID_ILocomotion=007a5890
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868
// @ref ?Swizzle@SwizzleManagerClass@@QAGJPAPAX@Z=0069fb20
// @ref ?Init@UnknownAudioController@@QAEXXZ=00405bf0
// @ref ??0?$VectorClass@PAVAbstractClass@@@@QAE@IPBQAVAbstractClass@@@Z=004ceb90
// @ref ??_7?$DynamicVectorClass@PAVAbstractClass@@@@6B@=007a177c
// @ref ?Release_Held@?$UnknownComPtr@UILocomotion@@$1?unknown_uuid_ILocomotion_7ce600@@3UGUID@@B@@QAEXXZ=004cdf80

WIN32_IMPORT HRESULT __stdcall OleLoadFromStream(IStream *stream, GUID const &iid, void **object);

HRESULT __stdcall FootClass::Load(IStream *stream)
{
    Locomotor.Attach(0);
    HRESULT result = TechnoClass::Load(stream);
    if (SUCCEEDED(result)) {
        int count;
        result = stream->Read(&count, sizeof(count), 0);
        if (FAILED(result)) {
            return result;
        }
        new (&unknown_478) DynamicVectorClass<AbstractClass *>;
        for (int index = 0; index < count; index++) {
            AbstractClass *pointer = 0;
            result = stream->Read(&pointer, sizeof(pointer), 0);
            if (FAILED(result)) {
                return result;
            }
            unknown_478.Add(pointer);
        }

        result = stream->Read(&count, sizeof(count), 0);
        if (FAILED(result)) {
            return result;
        }
        new (&unknown_49c) DynamicVectorClass<AbstractClass *>;
        for (index = 0; index < count; index++) {
            AbstractClass *pointer = 0;
            result = stream->Read(&pointer, sizeof(pointer), 0);
            if (FAILED(result)) {
                return result;
            }
            unknown_49c.Add(pointer);
        }

        Locomotor.Detach();
        OleLoadFromStream(stream, IID_ILocomotion, (void **)&Locomotor);
        unknown_490 = 0;
        Swizzle_Pointer(Team);
        Swizzle_Pointer(unknown_4c8);
        Swizzle_Pointer(unknown_494);
        Swizzle_Pointer(unknown_498);
        Swizzle_Pointer(unknown_4b8);
        Swizzle_Pointer(unknown_4bc);
        Swizzle_Pointer(unknown_4cc);
        Swizzle_Pointer(unknown_580);
        Swizzle_Pointer(unknown_588);
        unknown_43c.Init();
        unknown_434 = false;
        unknown_438 = 0;
        for (index = 0; index < unknown_49c.Count(); index++) {
            Swizzle_Pointer(unknown_49c[index]);
        }
        for (index = 0; index < unknown_478.Count(); index++) {
            Swizzle_Pointer(unknown_478[index]);
        }
        result = S_OK;
    }
    return result;
}
