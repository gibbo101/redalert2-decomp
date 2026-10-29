// void HouseClass::unknown_func_4f3720(int arg1) (0x004F3720)
// The money mode (+0x12C) of a computer house outside the campaign, by its
// Available_Money against Rules AIAlternateProductionCreditCutoff; mode 1
// may end when the house owns a BuildBarracks and a BuildWeapons type, has
// the power, and a coin flip says so; arg1 6 picks mode 2 (meaning not recovered).
#include "shared/techno.hpp"
#include "shared/rules.hpp"
#include "shared/building_type_class.hpp"
#include "shared/id_source.hpp"

void HouseClass::unknown_func_4f3720(int arg1)
{
    if (Is_Human_Control() || unknown_game_mode_a3d298 == 0) {
        return;
    }
    switch (unknown_12c) {
    case 1:
        if (Available_Money() < Rules->AIAlternateProductionCreditCutoff) {
            if (arg1 == 6) {
                unknown_12c = 2;
            }
        } else {
            unknown_12c = 0;
        }
        break;
    case 2:
        if (Available_Money() < Rules->AIAlternateProductionCreditCutoff) {
            bool barracks = false;
            for (int index = 0; index < Rules->BuildBarracks.Count(); index++) {
                barracks = barracks || unknown_5460.unknown_func_491d10(Rules->BuildBarracks[index]->ArrayIndex) > 0;
            }
            bool factory = false;
            for (int index2 = 0; index2 < Rules->BuildWeapons.Count(); index2++) {
                factory = factory || unknown_5460.unknown_func_491d10(Rules->BuildWeapons[index2]->ArrayIndex) > 0;
            }
            if (!(factory && barracks && Drain <= Power && Random_Pick(0, 1) != 0) && arg1 != 6) {
                unknown_12c = 1;
            }
        } else {
            unknown_12c = 0;
        }
        break;
    case 3:
        if (Available_Money() > Rules->AIAlternateProductionCreditCutoff) {
            unknown_12c = 0;
        }
        break;
    case 0:
        if (Available_Money() < Rules->AIAlternateProductionCreditCutoff) {
            unknown_12c = (arg1 == 6) + 1;
        }
        break;
    }
}
