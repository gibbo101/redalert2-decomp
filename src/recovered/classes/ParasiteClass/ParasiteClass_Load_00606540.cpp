// ?Load@ParasiteClass@@UAGJPAUIStream@@@Z (0x00606540)
// AbstractClass load, vtables, rejoins the update list, pointer fixups.
#include "shared/parasite.hpp"
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120
// @ref ?Swizzle@SwizzleManagerClass@@QAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868
// @ref ?unknown_abstracts_ac0bf8@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0bf8

HRESULT __stdcall ParasiteClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) ParasiteClass(NoInitClass());
        if (Victim != 0) {
            unknown_abstracts_ac0bf8.Add(this);
        }
        SwizzleManager.Swizzle((void **)&Owner);
        SwizzleManager.Swizzle((void **)&unknown_28);
        SwizzleManager.Swizzle((void **)&Victim);
    }
    return result;
}
