// HRESULT __stdcall ParticleTypeClass::Load(IStream *stream) (0x00621B90)
// Loads the object type, restores the particle type in place, swizzles its
// warhead, rebuilds the colour list from the saved count and colours and
// reloads its image.
#include "shared/particle_system.hpp"
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref ??_7?$VectorClass@VRGBClass@@@@6B@=0079da54
// @ref ??_7?$TypeList@VRGBClass@@@@6B@=0079da74
// @ref ??_7?$DynamicVectorClass@VRGBClass@@@@6B@=007a8604
// @ref ??_G?$VectorClass@VRGBClass@@@@UAEPAXI@Z=0046db10
// @ref ??_G?$TypeList@VRGBClass@@@@UAEPAXI@Z=0046cf00
// @ref ??_G?$DynamicVectorClass@VRGBClass@@@@UAEPAXI@Z=00622040
// @ref ??4?$VectorClass@VRGBClass@@@@QAEAAV0@ABV0@@Z=0046dd20
// @ref ??8?$VectorClass@VRGBClass@@@@UBE_NABV0@@Z=0046d720
// @ref ?ID@?$VectorClass@VRGBClass@@@@UAEHABVRGBClass@@@Z=0046d8b0
// @ref ?ID@?$VectorClass@VRGBClass@@@@UAEHPBVRGBClass@@@Z=0046d900
// @ref ?Fetch@?$VectorClass@VRGBClass@@@@UBE?AVRGBClass@@H@Z=0046cda0
// @ref ?Resize@?$VectorClass@VRGBClass@@@@UAE_NHPBVRGBClass@@@Z=0046d780
// @ref ?Clear@?$VectorClass@VRGBClass@@@@UAEXXZ=0046d880
// @ref ?Clear@?$DynamicVectorClass@VRGBClass@@@@UAEXXZ=0046cd40
// @ref ?ID@?$DynamicVectorClass@VRGBClass@@@@UAEHABVRGBClass@@@Z=0046da30
// @ref ?ID@?$DynamicVectorClass@VRGBClass@@@@UAEHPBVRGBClass@@@Z=0046cd70
// @ref ?Resize@?$DynamicVectorClass@VRGBClass@@@@UAE_NHPBVRGBClass@@@Z=0046d930
// @ref ?Load@ObjectTypeClass@@UAGJPAUIStream@@@Z=005d7c30
// @ref ??0ObjectTypeClass@@QAE@ABVNoInitClass@@@Z=005d5a80
// @ref ??0?$DynamicVectorClass@VRGBClass@@@@QAE@IPBVRGBClass@@@Z=00621fa0
// @ref ?unknown_func_5d7630@ObjectTypeClass@@QAEXXZ=005d7630
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868
// @ref ??_7ParticleTypeClass@@6BIPersistStream@@@=007a8560
// @ref ??_7ParticleTypeClass@@6BIRTTITypeInfo@@@=007a8544
// @ref ??_7ParticleTypeClass@@6BINoticeSink@@@=007a853c
// @ref ??_7ParticleTypeClass@@6BINoticeSource@@@=007a8534
// @ref ??_GParticleTypeClass@@UAEPAXI@Z=00621e80

HRESULT __stdcall ParticleTypeClass::Load(IStream *stream)
{
    HRESULT result = ObjectTypeClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }
    new (this) ParticleTypeClass(NoInitClass());
    SwizzleManager.Swizzle((void **)&Warhead);
    int count = 0;
    result = stream->Read(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return result;
    }
    for (int index = 0; index < count; index++) {
        RGBClass color;
        result = stream->Read(&color, sizeof(color), 0);
        if (FAILED(result)) {
            return result;
        }
        ColorList.Add(color);
    }
    unknown_func_5d7630();
    return S_OK;
}
