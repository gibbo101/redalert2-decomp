// HRESULT __stdcall TeamClass::Load(IStream *stream) (0x006BAAE0)
// Restores the team in place and swizzles its pointers.
#include "shared/team.hpp"
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120
// @ref ??0AbstractClass@@QAE@ABVNoInitClass@@@Z=0040ff60
// @ref ??0UnknownTimer423F60@@QAE@ABVNoInitClass@@@Z=00423f60
// @ref ?Swizzle@SwizzleManagerClass@@QAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868
// @ref ??_7TeamClass@@6BIPersistStream@@@=007ac950
// @ref ??_7TeamClass@@6BIRTTITypeInfo@@@=007ac934
// @ref ??_7TeamClass@@6BINoticeSink@@@=007ac92c
// @ref ??_7TeamClass@@6BINoticeSource@@@=007ac924
// @ref ?Detach@TeamClass@@UAEXPAVAbstractClass@@_N@Z=006b9590
// @ref ?AI@TeamClass@@UAEXXZ=006b7ad0

HRESULT __stdcall TeamClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) TeamClass(NoInitClass());
        SwizzleManager.Swizzle((void **)&Class);
        SwizzleManager.Swizzle((void **)&Script);
        SwizzleManager.Swizzle((void **)&Owner);
        SwizzleManager.Swizzle((void **)&Tag);
        SwizzleManager.Swizzle((void **)&Member);
        SwizzleManager.Swizzle((void **)&unknown_38);
        SwizzleManager.Swizzle((void **)&unknown_40);
        SwizzleManager.Swizzle((void **)&unknown_34);
        SwizzleManager.Swizzle((void **)&unknown_3c);
        SwizzleManager.Swizzle((void **)&unknown_30);
        SwizzleManager.Swizzle((void **)&unknown_44);
        result = S_OK;
    }
    return result;
}
