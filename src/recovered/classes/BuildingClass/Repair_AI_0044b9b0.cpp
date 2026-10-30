// Decide AI repair/sale and apply each paid repair tick.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/rules.hpp"
#include "shared/id_source.hpp"
// @ref ?Unknown_004F52F0@HouseClass@@=004f52f0
// @ref ?Unknown_004E5280@HouseClass@@=004e5280
// @ref ?Health_Ratio@ObjectClass@@=005d4540
// @ref __real@8@4006e100000000000000=0079d138
// @ref ?operator()@Random2Class@@=006388a0
void BuildingClass::Repair_AI_0044b9b0()
{
    if (House->unknown_194 >= Rules->IQRepairSell && unknown_slot91() != 18 && unknown_slot91() != 19 && unknown_slot36()) {
        if (House->Available_Money() >= Rules->CreditReserve) {
            if (!House->unknown_18c && !unknown_5b8 && (unknown_5b3 || unknown_59b || House->Unknown_004F52F0())) {
                House->unknown_18c = true;
                unknown_slot97(1);
                if (!House->Unknown_004F52F0()) {
                    House->unknown_1c8 = Random_Pick((int)(House->unknown_108 * 225.0), (int)(House->unknown_108 * 1800.0));
                }
            }
        } else {
            if ((unknown_game_mode_a3d298 != 0 || unknown_5ac) && unknown_329 && (unsigned)House->unknown_118 >= (unsigned)Rules->IQSellBack && (unsigned)Random_Pick(0, 50) < (unsigned)House->unknown_11c && unknown_34 == 0 && Type->Factory != 7 && Health_Ratio() < Rules->unknown_1370) {
                unknown_slot98(1);
            }
        }
    }
    if (unknown_5b8 && Frame % (int)(Rules->unknown_1348 * 900.0) == 0) {
        unknown_5ae = !unknown_5ae;
        int cost = Type->Repair_Cost();
        int step = Type->Repair_Step();
        int old_frame = unknown_43be20();
        if (House->Available_Money() >= cost) {
            House->Unknown_004E5280(cost);
            Strength += step;
            unknown_70 += step;
            if (Strength >= Type->MaxStrength) {
                unknown_70 = Strength = Type->MaxStrength;
                unknown_5b8 = false;
            }
            unknown_44d070(Health_Ratio() <= Rules->unknown_1368);
            if (Health_Ratio() > Rules->unknown_1368 && unknown_25c[3]) unknown_25c[3]->unknown_slot60();
            if (unknown_43be20() != old_frame) unknown_75 = true;
        } else {
            unknown_5b8 = false;
        }
    }
}
