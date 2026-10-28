// HRESULT __stdcall InfantryClass::Load(IStream *stream) (0x00508570, slot 5)
// Leaves the techno index, loads the foot, rebuilds itself in place while
// keeping the locomotor, rejoins the index and fixes up pointers.
#include "shared/infantry.hpp"
// @ref ?Load@FootClass@@UAGJPAUIStream@@@Z=004c9d10
// @ref ??0FootClass@@QAE@ABVNoInitClass@@@Z=004c2c60
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?unknown_object_index_abff58@@3V?$IndexClass@JPAVAbstractClass@@@@A=00abff58
// @ref ?Search_For_Node@?$IndexClass@JPAVAbstractClass@@@@ABEPBUNodeElement@1@ABJ@Z=0041b990
// @ref ?Increase_Table_Size@?$IndexClass@JPAVAbstractClass@@@@QAE_NH@Z=0041b900
// @ref ??_7InfantryClass@@6BIPersistStream@@@=007a3540
// @ref ??_7InfantryClass@@6BIRTTITypeInfo@@@=007a3524
// @ref ??_7InfantryClass@@6BINoticeSink@@@=007a351c
// @ref ??_7InfantryClass@@6BINoticeSource@@@=007a3514

HRESULT __stdcall InfantryClass::Load(IStream *stream)
{
    unknown_object_index_abff58.Remove_Index(Fetch_ID());
    HRESULT result = FootClass::Load(stream);
    if (SUCCEEDED(result)) {
        ILocomotion *locomotor = Locomotor;
        new (this) InfantryClass(NoInitClass());
        Locomotor = locomotor;
        locomotor->Release();
        unknown_object_index_abff58.Add_Index(Fetch_ID(), this);
        Swizzle_Pointer(Type);
        Swizzle_Pointer(unknown_40c);
        Swizzle_Pointer(unknown_410);
        result = S_OK;
    }
    return result;
}
