// @ref ??_C@_08JKPC@SGRYSMK1?$AA@=007ce620
// AircraftClass AI 0x004147F0. Unknown fields retain observed offsets; behavior names remain hypotheses.
#include "shared/aircraft.hpp"
#include "shared/infantry.hpp"
#include "shared/anim.hpp"
#include "shared/map_view.hpp"
#include "shared/random.hpp"
// @ref ?AI@FootClass@@UAEXXZ=004c8ff0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?Frame@@3HA=00a40d2c
// @ref ?AnimTypes@@3V?$TypeList@PAVAnimTypeClass@@@@A=008661e0
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8
// @ref ?From_Name@AnimTypeClass@@SIHPBD@Z=00425640
extern CellClass unknown_dummy_cell_a6f9f8;
void AircraftClass::AI()
{
    switch (Mission) {
    case 1:
    case 27:
        break;
    default:
        unknown_5ba = false;
    }
    if (unknown_20c) unknown_20c->AI();
    if ((unknown_slot111() || unknown_slot112()) && Frame % 24 == 0 && Rules->unknown_2a8)
        new AnimClass(Rules->unknown_2a8, CoordStruct(Coord), 0, 1, 0x600, 0);
    if (unknown_slot112() || (unknown_slot111() && unknown_210)) {
        Locomotor.Checked()->Process();
        if (!unknown_7d) return;
    }
    if ((unknown_slot112() && unknown_20c) || unknown_slot111()) {
        if (unknown_228) unknown_slot220(0);
        if (unknown_494) unknown_slot260(0, 1);
        return;
    }
    if (unknown_228) {
        if (((ObjectClass *)unknown_228)->unknown_slot21()) unknown_slot220(0);
        else if (unknown_228) {
            unsigned char const &target_is_techno = unknown_228->unknown_14_bit0;
            if (target_is_techno && !House->Is_Ally((ObjectClass *)unknown_228) &&
                ((TechnoClass *)unknown_228)->unknown_1b8 == 2 &&
                !((TechnoClass *)unknown_228)->unknown_slot192(House)) unknown_slot220(0);
        }
    }
    FootClass::AI();
    if (!unknown_7d) return;
    if (unknown_325) {
        CoordStruct current = Coord;
        unknown_slot103(current - CoordStruct(0, 0, 5));
        if (unknown_slot108() < -400) {
            unknown_slot55(0);
            unknown_slot60();
            return;
        }
        if ((Frame & 3) == 0) {
            int offset_y = unknown_id_source_a3d290->Random()(-170, 170);
            int offset_x = unknown_id_source_a3d290->Random()(-170, 170);
            CoordStruct offset(offset_x, offset_y, -unknown_slot108());
            current = Coord;
            current = current + offset;
            new AnimClass(Rules->unknown_09c, current, 0, 1, 0x600, 0);
        }
    }
    CoordStruct position = Coord;
    if (Type->Trailer && Frame % Type->SpawnDelay == 0)
        new AnimClass(Type->Trailer, position, 1, 1, 0x600, 0);
    if (!Map.Unknown_0055A660(unknown_slot104(), true) && unknown_slot282()) {
        unknown_slot60();
        return;
    }
    if (unknown_494 == &unknown_dummy_cell_a6f9f8) {
        unknown_slot260(0, 1);
        unknown_slot220(0);
        unknown_slot261(false, true);
    }
    if (unknown_228 == &unknown_dummy_cell_a6f9f8) {
        unknown_slot260(0, 1);
        unknown_slot220(0);
        unknown_slot261(false, true);
    }
    if (unknown_slot122()) unknown_slot117();
    if (unknown_5b0 && Mission != 1) {
        unknown_5b0 = false;
        --unknown_254;
    }
    if (Health_Ratio() < Rules->unknown_1370 && unknown_slot108() > 0) {
        int chance = Strength != 0 ? 10 : 80;
        if (unknown_id_source_a3d290->Random()(0, 99) < chance)
            new AnimClass(AnimTypes[AnimTypeClass::From_Name("SGRYSMK1")], CoordStruct(Coord), 0, 1, 0x600, 0);
    }
    if (Cargo.Object && Type->Carryall) {
        ((TechnoClass *)Cargo.unknown_468a10())->unknown_2e0 = unknown_2f8;
        ((TechnoClass *)Cargo.unknown_468a10())->unknown_2f8 = unknown_2f8;
        CoordStruct passenger_position = Coord;
        Cargo.unknown_468a10()->unknown_slot103(passenger_position);
    }
}
