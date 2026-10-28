// HRESULT __stdcall IsometricTileTypeClass::Load(IStream *stream) (0x0052E1C0, slot 5)
// Releases every light converter, loads the object type, restores the
// virtual tables (and an empty unknown_274) in place, fixes up unknown_28c,
// forgets the converters again and rebuilds unknown_274.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/isometric_tile_type.hpp"
// @ref ??_7IsometricTileTypeClass@@6BIPersistStream@@@=007a51a8
// @ref ??_7IsometricTileTypeClass@@6BIRTTITypeInfo@@@=007a518c
// @ref ??_7IsometricTileTypeClass@@6BINoticeSink@@@=007a5184
// @ref ??_7IsometricTileTypeClass@@6BINoticeSource@@@=007a517c
// @ref ??_7?$DynamicVectorClass@PAG@@6B@=007a524c
// @ref ??0?$VectorClass@PAG@@QAE@IPBQAG@Z=0052ed90
// @ref ??1IsometricTileTypeClass@@UAE@XZ=00529190
// @ref ??_GIsometricTileTypeClass@@UAEPAXI@Z=0052e6b0
// @ref ??_EIsometricTileTypeClass@@UAEPAXI@Z=0052e6b0
// @ref ?GetClassID@IsometricTileTypeClass@@UAGJPAUGUID@@@Z=0052e2d0
// @ref ?Save@IsometricTileTypeClass@@UAGJPAUIStream@@H@Z=0052e2b0
// @ref ?Detach@IsometricTileTypeClass@@UAEXPAVAbstractClass@@_N@Z=0052e310
// @ref ?Kind_Of@IsometricTileTypeClass@@UBEHXZ=0052e680
// @ref ?Size_Of@IsometricTileTypeClass@@UBEHXZ=0052e690
// @ref ?Compute_CRC@IsometricTileTypeClass@@UBEXAAVWWCRCEngine@@@Z=0052e0b0
// @ref ?unknown_slot16@IsometricTileTypeClass@@UBEHXZ=0052e6a0
// @ref ?unknown_slot27@IsometricTileTypeClass@@UBE?AUCoordStruct@@ABU2@@Z=0052e090
// @ref ?unknown_slot32@IsometricTileTypeClass@@UBE_NABVCell@@PAVHouseClass@@@Z=0052dfe0
// @ref ?unknown_slot35@IsometricTileTypeClass@@UBEPAVObjectClass@@PAVHouseClass@@@Z=0052e020
// @ref ?unknown_slot36@IsometricTileTypeClass@@UBEPBVCell@@H@Z=00529450
// @ref ?unknown_slot39@IsometricTileTypeClass@@UBEPAXXZ=005293d0
// @ref ??_G?$DynamicVectorClass@PAG@@UAEPAXI@Z=0052eca0
// @ref ??_E?$DynamicVectorClass@PAG@@UAEPAXI@Z=0052eca0
// @ref ??8?$VectorClass@PAG@@UBE_NABV0@@Z=0052e790
// @ref ?Resize@?$DynamicVectorClass@PAG@@UAE_NHPBQAG@Z=0052e910
// @ref ?Clear@?$DynamicVectorClass@PAG@@UAEXXZ=0052e6d0
// @ref ?ID@?$DynamicVectorClass@PAG@@UAEHABQAG@Z=0052e9c0
// @ref ?ID@?$DynamicVectorClass@PAG@@UAEHPBQAG@Z=0052e700
// @ref ?Fetch@?$VectorClass@PAG@@UBEPAGH@Z=0052e720
// @ref ?Read_INI@ObjectTypeClass@@UAE_NAAVCCINIClass@@@Z=005d7810
// @ref ?unknown_slot28@ObjectTypeClass@@UBEHXZ=00426760
// @ref ?Who_Can_Build_Me@ObjectTypeClass@@UBEPAVBuildingClass@@_N00PAVHouseClass@@@Z=005d5fc0
// @ref ?unknown_slot29@ObjectTypeClass@@UBEHXZ=005d5d00
// @ref ?unknown_slot30@ObjectTypeClass@@UBE?AUCoordStruct@@XZ=005d5d10
// @ref ?unknown_slot31@ObjectTypeClass@@UBE?AUCoordStruct@@XZ=005d5d30
// @ref ?unknown_slot33@ObjectTypeClass@@UBEHH@Z=005d5d60
// @ref ?unknown_slot34@ObjectTypeClass@@UBEHXZ=005d5d70
// @ref ?unknown_slot38@ObjectTypeClass@@UBEHXZ=005d5d80
// @ref ?GetSizeMax@ObjectTypeClass@@UAGJPATULARGE_INTEGER@@@Z=005d7e80
// @ref ?Load@ObjectTypeClass@@UAGJPAUIStream@@@Z=005d7c30
// @ref ??0ObjectTypeClass@@QAE@ABVNoInitClass@@@Z=005d5a80
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868
// @ref ?unknown_func_52e3d0@IsometricTileTypeClass@@QAEXXZ=0052e3d0
// @ref ?unknown_LightConvertClass_list_00832398@@3V?$DynamicVectorClass@PAVLightConvertClass@@@@A=00832398


HRESULT __stdcall IsometricTileTypeClass::Load(IStream *stream)
{
    int index;
    for (index = 0; index < unknown_LightConvertClass_list_00832398.Count(); index++) {
        delete unknown_LightConvertClass_list_00832398[index];
        unknown_LightConvertClass_list_00832398[index] = 0;
    }

    HRESULT result = ObjectTypeClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }
    new (this) IsometricTileTypeClass(NoInitClass());
    SwizzleManager.Swizzle((void **)&unknown_28c);

    for (index = 0; index < unknown_LightConvertClass_list_00832398.Count(); index++) {
        unknown_LightConvertClass_list_00832398[index] = 0;
    }
    unknown_func_52e3d0();
    return S_OK;
}
