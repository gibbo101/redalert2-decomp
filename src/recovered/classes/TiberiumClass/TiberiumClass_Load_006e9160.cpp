// HRESULT TiberiumClass::Load(IStream *stream) (0x006E9160)
// Drops the spread and growth queues and the debris list, loads the base type, restores the object
// in place and the debris list, fixes up the pointers and leaves the queues to be rebuilt (TibSun
// tiberium.cpp).
#include "shared/tiberium.hpp"
#include "shared/abstract.hpp"
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120
// @ref ??0?$CDTimerClass@VFrameTimerClass@@@@QAE@J@Z=00463f80

HRESULT __stdcall TiberiumClass::Load(IStream *stream)
{
    Clear_Spread();
    Clear_Growth();
    Debris.Clear();

    HRESULT result = AbstractClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) TiberiumClass(NoInitClass());
        Swizzle_Pointer(Image);
        Debris.Load(stream);
        for (int index = 0; index < Debris.Count(); index++) {
            Swizzle_Pointer(Debris[index]);
        }
        GrowthQueue = 0;
        GrowthMap = 0;
        GrowthData = 0;
        SpreadQueue = 0;
        SpreadMap = 0;
        SpreadData = 0;
        result = S_OK;
    }
    return result;
}
