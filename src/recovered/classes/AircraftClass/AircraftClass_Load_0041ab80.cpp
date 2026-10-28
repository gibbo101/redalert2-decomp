// HRESULT __stdcall AircraftClass::Load(IStream *stream) (0x0041AB80, slot 5)
// Leaves the techno index, loads the foot, rebuilds itself in place while
// keeping the locomotor, rejoins the index and fixes up pointers.
#include "shared/aircraft.hpp"
// @ref ?Load@FootClass@@UAGJPAUIStream@@@Z=004c9d10
// @ref ??0FootClass@@QAE@ABVNoInitClass@@@Z=004c2c60
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?unknown_object_index_abff58@@3V?$IndexClass@JPAVAbstractClass@@@@A=00abff58
// @ref ?Search_For_Node@?$IndexClass@JPAVAbstractClass@@@@ABEPBUNodeElement@1@ABJ@Z=0041b990
// @ref ?Increase_Table_Size@?$IndexClass@JPAVAbstractClass@@@@QAE_NH@Z=0041b900
// @ref ??_7AircraftClass@@6BIPersistStream@@@=0079b12c
// @ref ??_7AircraftClass@@6BIRTTITypeInfo@@@=0079b110
// @ref ??_7AircraftClass@@6BINoticeSink@@@=0079b108
// @ref ??_7AircraftClass@@6BINoticeSource@@@=0079b100
// @ref ??_7AircraftClass@@6BIFlyControl@@@=0079b0d8

HRESULT __stdcall AircraftClass::Load(IStream *stream)
{
    unknown_object_index_abff58.Remove_Index(Fetch_ID());
    HRESULT result = FootClass::Load(stream);
    if (SUCCEEDED(result)) {
        ILocomotion *locomotor = Locomotor;
        new (this) AircraftClass(NoInitClass());
        Locomotor = locomotor;
        locomotor->Release();
        unknown_object_index_abff58.Add_Index(Fetch_ID(), this);
        Swizzle_Pointer(Type);
        Swizzle_Pointer(unknown_5b4);
        result = S_OK;
    }
    return result;
}
