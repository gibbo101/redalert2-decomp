// Selects an infantry animation sequence, sound, rate and start frame (0x00504740).
#include "shared/infantry.hpp"
#include "shared/techno_map.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_00713E60@@YIXHABUCoordStruct@@H@Z=00713e60
// @ref ?unknown_do_controls_7a3474@@3PAUDoStruct@@A=007a3474
// @ref ?unknown_frame_rate_a40b18@@3VUnknownFrameRateControl@@A=00a40b18
// @ref ?Adjust_005d9760@UnknownFrameRateControl@@QBEHH@Z=005d9760
// @ref ?Frame@@3HA=00a40d2c
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
bool InfantryClass::unknown_slot311(int sequence, bool force, bool random_start)
{
    if (sequence == -1 || Type->DoControls[sequence].Count == 0) {
        return false;
    }
    if (Sequence == 33 && unknown_7a) {
        return false;
    }
    if (Type->MovementZone == 3) {
        UnknownCellClass *cell = Map_Cell_At(unknown_slot104());
        int on_land = 1;
        if ((cell->unknown_ec == 6 || cell->unknown_ec == 2) && !unknown_79) {
            on_land = 0;
            if (sequence == 3 || sequence == 6) sequence = 17;
            else if (sequence == 2 || sequence == 0) sequence = 16;
            else if (sequence == 9) sequence = 18;
            else if (sequence == 10) sequence = 19;
            else if (sequence == 11) sequence = 20;
            else if (sequence == 12) sequence = 21;
            else if (sequence == 4 || sequence == 8) sequence = 22;
        }
        if (unknown_5d0 == 0 && on_land == 1) {
            CoordStruct coord = Coord;
            Unknown_00713E60(Type->LeaveWaterSound, coord, 0);
        } else if (unknown_5d0 == 1 && on_land == 0) {
            CoordStruct coord = Coord;
            Unknown_00713E60(Type->EnterWaterSound, coord, 0);
        }
        unknown_5d0 = on_land;
    }
    if (unknown_slot21() && !unknown_79 && Type->DoControls[23].Frame > 0 && sequence == 0) {
        sequence = 23;
    } else if (sequence == 3 && unknown_5bc >= 200) {
        sequence = 37;
    }
    if (sequence == Sequence || (Sequence != -1 && !force && !unknown_do_controls_7a3474[Sequence].Interrupt)) {
        return false;
    }
    if (sequence == 27) {
        if (unknown_slot32()->DeploySound != -1) {
            CoordStruct coord = Coord;
            Unknown_00713E60(unknown_slot32()->DeploySound, coord, 0);
        }
    } else if (sequence == 31 && unknown_slot32()->UndeploySound != -1) {
        CoordStruct coord = Coord;
        Unknown_00713E60(unknown_slot32()->UndeploySound, coord, 0);
    }
    Sequence = sequence;
    if (Is_Prone_Sequence_005096e0(sequence)) {
        int rate = unknown_frame_rate_a40b18.Adjust_005d9760(unknown_do_controls_7a3474[sequence].Rate);
        AnimationStage.Set_Rate(rate);
    } else {
        int rate = unknown_do_controls_7a3474[sequence].Rate;
        AnimationStage.Set_Rate(rate);
    }
    if (random_start) {
        int count = Type->DoControls[sequence].Count;
        if (count <= 1) count = 1;
        AnimationStage.Value = unknown_id_source_a3d290->Random()(0, count - 1);
    } else {
        AnimationStage.Value = 0;
    }
    if (Strength == 0) {
        unknown_slot291();
    }
    switch (sequence) {
    case 5:
        unknown_5c3 = true;
        break;
    case 7:
    case 27:
        unknown_5c3 = false;
        return true;
    }
    return true;
}
