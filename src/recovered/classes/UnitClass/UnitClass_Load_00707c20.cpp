// HRESULT __stdcall UnitClass::Load(IStream *stream) (0x00707C20, slot 5)
// Leaves the techno index, loads the foot, rebuilds itself in place while
// keeping the locomotor, rejoins the index and fixes up pointers.
#include "shared/unit.hpp"
// @ref ?Load@FootClass@@UAGJPAUIStream@@@Z=004c9d10
// @ref ??0FootClass@@QAE@ABVNoInitClass@@@Z=004c2c60
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868
// @ref ?Swizzle@SwizzleManagerClass@@QAGJPAPAX@Z=0069fb20
// @ref ?unknown_object_index_abff58@@3V?$UnknownIndexClass@JPAVObjectClass@@@@A=00abff58
// @ref ?Search_For_Node@?$UnknownIndexClass@JPAVObjectClass@@@@QAEPBUNodeElement@1@ABJ@Z=0041b990
// @ref ?Increase_Table_Size@?$UnknownIndexClass@JPAVObjectClass@@@@QAE_NH@Z=0041b900
// @ref ??_7UnitClass@@6BIPersistStream@@@=007addf8
// @ref ??_7UnitClass@@6BIRTTITypeInfo@@@=007adddc
// @ref ??_7UnitClass@@6BINoticeSink@@@=007addd4
// @ref ??_7UnitClass@@6BINoticeSource@@@=007addcc

HRESULT __stdcall UnitClass::Load(IStream *stream)
{
    unknown_object_index_abff58.Remove_Index(Fetch_ID());
    HRESULT result = FootClass::Load(stream);
    if (SUCCEEDED(result)) {
        ILocomotion *locomotor = Locomotor;
        new (this) UnitClass(NoInitClass());
        Locomotor = locomotor;
        locomotor->Release();
        unknown_object_index_abff58.Add_Index(Fetch_ID(), this);
        Swizzle_Pointer(Type);
        Swizzle_Pointer(unknown_5b0);
        unknown_5c4 = 0;
        result = S_OK;
    }
    return result;
}
