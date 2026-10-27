// float HouseClass::Harvested(float amount, int type) (0x004E5100)
#include "shared/techno.hpp"

float HouseClass::Harvested(float amount, int type)
{
    unknown_5418 = (int)(amount * 5.0f + unknown_5418);
    Balance = (int)(((UnknownTiberiumView *)unknown_TiberiumClass_list_00ac0b30[type])->Value * Type->unknown_0x148 * amount + Balance);
    return amount;
}
