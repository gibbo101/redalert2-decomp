// bool AITriggerTypeClass::Neutral_Owns_Compare(HouseClass *house, HouseClass *enemy) const (0x0041CEF0)
// Finds the neutral house (the last house of the "Civilian" side) and
// compares how many objects of the condition type it owns with the
// comparator; false without a neutral house.
#include "shared/ai_trigger_type.hpp"
#include "shared/house.hpp"
#include "shared/side.hpp"
#include "shared/debug_printf.hpp"
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
// @ref ?Find_Index@SideClass@@SIHPBD@Z=0067af90
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0BE@HLHH@Neutral?5house?5is?5?$CFs?$AA@=007ceb1c
// @ref ??_C@_08NIHI@Civilian?$AA@=007ceb30
// @ref ?unknown_func_491d10@UnknownHouseCounter@@QAEHH@Z=00491d10


bool AITriggerTypeClass::Neutral_Owns_Compare(HouseClass *house, HouseClass *enemy) const
{
    bool result = false;
    HouseClass *neutral = 0;
    for (int index = 0; index < Houses.Count(); index++) {
        HouseClass *candidate = Houses[index];
        if (candidate->Type->Side == SideClass::Find_Index("Civilian")) {
            neutral = candidate;
        }
    }
    if (neutral != 0) {
        Debug_Printf("Neutral house is %s", (char const *)neutral->Type->ID);
        int count = Owned_Count(neutral);
        switch (((int const *)Comparator)[1]) {
        case 0:
            result = count < ((int const *)Comparator)[0];
            break;
        case 1:
            result = count <= ((int const *)Comparator)[0];
            break;
        case 2:
            result = count == ((int const *)Comparator)[0];
            break;
        case 3:
            result = count >= ((int const *)Comparator)[0];
            break;
        case 4:
            result = count > ((int const *)Comparator)[0];
            break;
        case 5:
            result = count != ((int const *)Comparator)[0];
            break;
        }
    }
    return result;
}
