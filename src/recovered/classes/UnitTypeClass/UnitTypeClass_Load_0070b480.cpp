// HRESULT __stdcall UnitTypeClass::Load(IStream *stream) (0x0070B480)
// Rebuilds the object in place, reloads the image and the alternate image.
#include "shared/unit_type.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/cc_file_class.hpp"
// @ref ?Load@TechnoTypeClass@@UAGJPAUIStream@@@Z=006de260
// @ref ??0TechnoTypeClass@@QAE@ABVNoInitClass@@@Z=006da6e0
// @ref ??_7UnitTypeClass@@6BIPersistStream@@@=007ae328
// @ref ??_7UnitTypeClass@@6BIRTTITypeInfo@@@=007ae30c
// @ref ??_7UnitTypeClass@@6BINoticeSink@@@=007ae304
// @ref ??_7UnitTypeClass@@6BINoticeSource@@@=007ae2fc
// @ref ?unknown_func_5d6730@ObjectTypeClass@@QAEXXZ=005d6730
// @ref ?unknown_func_5d7630@ObjectTypeClass@@QAEXXZ=005d7630
// @ref ??_C@_04BOIE@?4SHP?$AA@=007ced14
// @ref __makepath=007831f0
// @ref ?Retrieve@?$MixFileClass@VCCFileClass@@@@SIPBXPBD@Z=005956c0

HRESULT __stdcall UnitTypeClass::Load(IStream *stream)
{
    HRESULT result = TechnoTypeClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }
    new (this) UnitTypeClass(NoInitClass());
    unknown_func_5d6730();
    unknown_func_5d7630();
    if (AltImage) {
        char filename[260];
        _makepath(filename, 0, 0, AltImageFile, ".SHP");
        AltImage = MixFileClass<CCFileClass>::Retrieve(filename);
    }
    return S_OK;
}
