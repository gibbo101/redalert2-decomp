// int TechnoClass::unknown_slot95(RadioClass *from, int message, long &param) (0x006C2590, slot 95)
// The radio message handler (Westwood's Receive_Message; param is the
// message's long argument):
//   3: answers 0x19 to a sender with +0x370 when this has +0x370 too, then RadioClass's;
//   7, 9, 22: answers 0x18, then RadioClass's;   8: answers 0x19 and 3;
//   24: unless an AirportBound aircraft or already +0x370, sets it, answers 0x18;
//   25: clears +0x370, answers 0x19;  26/27: sets/clears +0x371, answers 0x1A/0x1B;
//   28: repairs one step for the type's repair cost (10 when not damaged, 0x20
//       when the owner cannot pay; restarts a riding parasite's timer; fully
//       repaired: 0x21 with Strength reset);
//   30: with a weapon, targets param and commences mission 1;
//   31: 10 at full ammunition, else one more;
// everything else goes to RadioClass. The handled messages answer 1.
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
#include "shared/foot.hpp"
#include "shared/parasite.hpp"
#include "shared/aircraft.hpp"
#include "shared/aircraft_type.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_slot95@RadioClass@@UAEHPAV1@HAAJ@Z=00636900
// @ref ?Health_Ratio@ObjectClass@@QBENXZ=005d4540
// @ref ?Unknown_004E5280@HouseClass@@QAEXH@Z=004e5280
// @ref ?Unknown_00607440@ParasiteClass@@QAEXXZ=00607440

int TechnoClass::unknown_slot95(RadioClass *from, int message, long &param)
{
    TechnoClass *sender = (TechnoClass *)from;
    switch (message) {
    case 30: {
        WeaponStruct *weapon = unknown_slot230();
        if (weapon == 0 || weapon->WeaponType == 0) {
            break;
        }
        unknown_slot220((AbstractClass *)param);
        unknown_slot116(1, false);
        return 1;
    }
    case 24: {
        if (Kind_Of() == 2) {
            AircraftClass *aircraft = this == 0 ? 0 : (Kind_Of() == 2 ? (AircraftClass *)this : 0);
            if (aircraft->Type->AirportBound) {
                break;
            }
        }
        if (unknown_370) {
            break;
        }
        unknown_370 = true;
        unknown_slot150(0x18, sender);
        return 1;
    }
    case 25:
        if (!unknown_370) {
            break;
        }
        unknown_370 = false;
        unknown_slot150(0x19, sender);
        return 1;
    case 26:
        if (unknown_371) {
            break;
        }
        unknown_371 = true;
        unknown_slot150(0x1A, sender);
        return 1;
    case 27:
        if (!unknown_371) {
            break;
        }
        unknown_371 = false;
        unknown_slot150(0x1B, sender);
        return 1;
    case 8:
        unknown_slot150(0x19, sender);
        return unknown_slot150(3, sender);
    case 3:
        if (unknown_370 && sender->unknown_370) {
            unknown_slot150(0x19, sender);
        }
        RadioClass::unknown_slot95(from, message, param);
        return 1;
    case 7:
    case 9:
    case 22:
        unknown_slot150(0x18, sender);
        RadioClass::unknown_slot95(from, message, param);
        return 1;
    case 31:
        if (unknown_254 == unknown_slot32()->Ammo) {
            return 10;
        }
        unknown_254++;
        return 1;
    case 28:
        if (Health_Ratio() < Rules->unknown_1360) {
            int cost = unknown_slot32()->Repair_Cost();
            int step = unknown_slot32()->Repair_Step();
            if (step <= 1) {
                step = 1;
            }
            if (House->Available_Money() >= cost) {
                if (cost != 0) {
                    House->Unknown_004E5280(cost);
                }
                Strength += step;
                unknown_70 += step;
                bool foot;
                if (this != 0) {
                    foot = AbstractFlags.IsFoot;
                }
                if (this != 0 && foot && ((FootClass *)this)->unknown_580 != 0) {
                    ((FootClass *)this)->unknown_580->unknown_588->unknown_2c = 50;
                    ((FootClass *)this)->unknown_580->unknown_588->Unknown_00607440();
                }
                if (Health_Ratio() > Rules->unknown_1368 || unknown_slot108() < -10) {
                    if (unknown_25c[3] != 0) {
                        unknown_25c[3]->unknown_slot60();
                    }
                }
                if (Health_Ratio() < Rules->unknown_1360) {
                    return 1;
                }
                int strength = unknown_slot32()->MaxStrength;
                Strength = strength;
                unknown_70 = strength;
                return 0x21;
            }
            return 0x20;
        }
        return 10;
    }
    return RadioClass::unknown_slot95(from, message, param);
}
