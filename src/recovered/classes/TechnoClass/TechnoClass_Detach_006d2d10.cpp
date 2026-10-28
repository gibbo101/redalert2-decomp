// void TechnoClass::Detach(AbstractClass *target, bool all) (0x006D2D10, slot 10)
// Forgets an object that is going away: RadioClass's part, the passenger
// (all), +0x23C and +0x20C; the target (+0x228; kept while the target's cell
// stays visible to the owner unless all, and only when it belongs to another
// house or all) after re-arming the +0x148 timer to 4-8 frames when more than
// 10 remain, clearing it through slot 220 and restoring a suspended mission
// (an aircraft on mission 0x19 also drops +0xA8 and +0x5BA); +0x22C likewise;
// the owner; the slot 51 object when slot 48; the eight +0x25C slots, +0x27C;
// with all, +0x3F8, +0x1B0 and the capture manager's hold; the spawn and
// temporal helpers; +0x384, +0x108; and the target's entries in the +0x390 /
// +0x3A8 / +0x3C0 lists.
#include "shared/techno.hpp"
#include "shared/spawn_manager.hpp"
#include "shared/house.hpp"
#include "shared/aircraft.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
// @ref ?Detach@RadioClass@@UAEXPAVAbstractClass@@_N@Z=00636ba0
// @ref ?Unknown_00468A70@UnknownCargo@@QAEXPAVFootClass@@@Z=00468a70
// @ref ?unknown_47c2e0@UnknownCellClass@@QAE_NH@Z=0047c2e0
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?Unknown_00468120@UnknownTechno230@@QAEXPAVAbstractClass@@@Z=00468120
// @ref ?Unlink@SpawnManagerClass@@QAEXPAVAbstractClass@@@Z=0068a560
// @ref ?Unknown_006E24C0@UnknownTechno208@@QAEXPAVAbstractClass@@@Z=006e24c0

void TechnoClass::Detach(AbstractClass *target, bool all)
{
    RadioClass::Detach(target, all);
    if (all) {
        Cargo.Unknown_00468A70((FootClass *)target);
    }
    bool forget = true;
    if (target == unknown_23c) {
        unknown_23c = 0;
    }
    if (target == unknown_20c) {
        unknown_20c = 0;
    }
    bool object;
    if (!all && target != 0) {
        object = target->unknown_14_bit0;
    }
    if (!all && target != 0 && object) {
        if (Map_Cell(target->Center_Coord())->unknown_47c2e0(House->ArrayIndex)) {
            forget = false;
        }
    }
    if (unknown_228 == target && forget && (all || target->Owning_House() != House)) {
        if (unknown_148.Value() > 10 && unknown_a40774 == 0) {
            unknown_148 = unknown_id_source_a3d290->Random()(4, 8);
        }
        unknown_slot220(0);
        if (unknown_slot121()) {
            unknown_slot120();
            if (Kind_Of() == 2 && Mission == 0x19) {
                unknown_a8 = 0;
                ((AircraftClass *)this)->unknown_5ba = false;
            }
        }
    }
    if (unknown_22c == target && forget) {
        unknown_22c = 0;
    }
    if (House == target) {
        House = 0;
        unknown_372 = false;
    }
    if (unknown_slot48() && unknown_slot51(true) == target) {
        unknown_slot256();
    }
    for (int slot = 0; slot < 8; slot++) {
        if (unknown_25c[slot] == target) {
            unknown_25c[slot] = 0;
        }
    }
    if (unknown_27c == target) {
        unknown_27c = 0;
    }
    if (all) {
        if (unknown_3f8 == target) {
            unknown_3f8 = 0;
        }
        if (unknown_1b0 == target) {
            unknown_1b0 = 0;
        }
        if (unknown_230 != 0) {
            ((UnknownTechno230 *)unknown_230)->Unknown_00468120(target);
        }
    }
    if (SpawnManager != 0) {
        SpawnManager->Unlink(target);
    }
    if (unknown_208 != 0) {
        unknown_208->Unknown_006E24C0(target);
    }
    if (target == unknown_384) {
        unknown_384 = 0;
    }
    if (target == unknown_108) {
        unknown_108 = 0;
    }
    // The list removals take `&*target`, an rvalue: the original passes a
    // temporary copy of the pointer, never the parameter's own slot.
    int index = -1;
    for (int i = 0; i < unknown_3a8.Count(); i++) {
        if (target == unknown_3a8[i]) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        unknown_390.Delete(index);
        unknown_3a8.Delete(&*target);
    }
    unknown_3c0.Delete(&*target);
}
