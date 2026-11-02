// int BuildingClass::unknown_slot129() (0x00445620)
// The building's guard mission (hypothesis: Mission_Guard); returns the
// delay until the next call. While slot 163 holds (marking unknown_5ad), a
// building with a usable super weapon (its auxiliary building owned) and
// an occupant or no occupant slots, and a +0x228 object, switches to
// mission 1 at once; otherwise it waits the mission's +0x18 rate. A stupid
// guard waits 100. Otherwise the first call (status 0) runs 0x00443D60 and
// moves to status 1; in status 1 a repair or reload bay starts mission
// 0x14 with the first contact in mission 7 within 64 leptons that accepts
// message 0x13, and a weapons factory runs 0x004454B0. A reload bay in
// radio contact then starts mission 0x14 when message 0x1D is refused and
// 0x13 accepted. The delay is the mission's +0x10 rate (three times that
// for buildings that are not repair bays) plus 0..2.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/super_weapon_type.hpp"
#include "shared/unknown_vector3.hpp"
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref _unknown_id_source_a3d290=00a3d290
// @ref __real@8@4008e100000000000000=0079b608
// @ref ?Supers@@3V?$DynamicVectorClass@PAVSuperClass@@@@A=00a35d28
// @ref ?unknown_func_491d10@UnknownHouseCounter@@QAEHH@Z=00491d10
// @ref ?Contact@RadioClass@@QBEPAVTechnoClass@@H@Z=00636e10
// @ref ??0UnknownVector3@@QAE@HHH@Z=0041b630
// @ref ?Length@UnknownVector3@@QBEHXZ=0041b780
// @ref ?unknown_443d60@BuildingClass@@QAEX_N@Z=00443d60
// @ref ?unknown_4454b0@BuildingClass@@QAEXXZ=004454b0
// @ref ?In_Radio_Contact@RadioClass@@QBE_NXZ=00636f10

// The difference of two coordinates (an inline helper).
inline UnknownVector3 Coord_Difference(CoordStruct const &a, CoordStruct const &b)
{
    return UnknownVector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
}

int BuildingClass::unknown_slot129()
{
    if (unknown_slot163()) {
        unknown_5ad = true;
        if (!Type->EMPulseCannon) {
            int super = Type->SuperWeapon;
            if (super != -1) {
                BuildingTypeClass *aux = Supers[super]->Type->AuxBuilding;
                if (aux != 0 && House->unknown_5460.unknown_func_491d10(aux->ArrayIndex) == 0) {
                    goto check_occupants;
                }
            }
            if (Type->SuperWeapon == -1) {
check_occupants:
                if ((!Type->CanBeOccupied || unknown_554.Count() > 0) && unknown_228 != 0) {
                    unknown_slot116(1, false);
                    unknown_slot117();
                    return 1;
                }
            }
        }
        int delay = (int)(Control()->unknown_18 * 900.0);
        return delay + unknown_id_source_a3d290->Random()(0, 2);
    }
    if (Type->HasStupidGuardMode) {
        return 100;
    }
    switch (unknown_a8) {
    case 0:
        unknown_443d60(true);
        unknown_a8 = 1;
        break;
    case 1:
        if (Type->UnitRepair || Type->UnitReload) {
            for (int index = 0; index < RadioLinks.Length(); index++) {
                TechnoClass *techno = Contact(index);
                bool active;
                if (techno != 0) {
                    active = techno->AbstractFlags.IsTechno;
                }
                if (techno != 0 && active) {
                    if (techno->unknown_slot91() == 7) {
                        UnknownVector3 distance = Coord_Difference(Center_Coord(), techno->Center_Coord());
                        if (distance.Length() < 0x40
                            && unknown_slot150(0x13, techno) == 1) {
                            unknown_slot116(0x14, false);
                            return 1;
                        }
                    }
                }
            }
        }
        if (Type->WeaponsFactory) {
            unknown_4454b0();
        }
        break;
    }
    if (Type->UnitReload && In_Radio_Contact() && unknown_slot149(0x1D) != 1 && unknown_slot149(0x13) == 1) {
        unknown_slot116(0x14, false);
    }
    if (Type->UnitRepair) {
        int delay = (int)(Control()->unknown_10 * 900.0);
        return delay + unknown_id_source_a3d290->Random()(0, 2);
    }
    int delay = (int)(Control()->unknown_10 * 900.0);
    return delay * 3 + unknown_id_source_a3d290->Random()(0, 2);
}
