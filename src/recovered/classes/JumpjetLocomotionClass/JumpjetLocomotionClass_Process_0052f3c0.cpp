// bool __stdcall JumpjetLocomotionClass::Process() (0x0052F3C0, ILocomotion 16)
// While moving: the movement step (0x00530B00); a dead object stops here.
// Held locomotors (house 0x0051FC80) outside states 0 and 5 call slot 224;
// a crashing techno (+0x37D) with height enters state 5 (infantry play
// sequence 0x22). Then the state routine runs and the object is revealed
// or shrouded for the player. A changed layer resubmits the object.
#include "shared/jumpjet_locomotion.hpp"
#include "shared/house.hpp"
#include "shared/infantry.hpp"
#include "shared/id_source.hpp"
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_530180@JumpjetLocomotionClass@@QAEXXZ=00530180
// @ref ?unknown_530550@JumpjetLocomotionClass@@QAEXXZ=00530550
// @ref ?unknown_530b00@JumpjetLocomotionClass@@QAEXXZ=00530b00

bool __stdcall JumpjetLocomotionClass::Process()
{
    int layer = Layer();
    if (Is_Moving() || Is_Moving_Now()) {
        unknown_530b00();
        if (!LinkedTo->unknown_7d) {
            return false;
        }
        if (LinkedTo->House->Unknown_0051FC80() && unknown_4c != 0 && unknown_4c != 5) {
            LinkedTo->unknown_slot224(0);
        }
        if (LinkedTo->unknown_37d && unknown_4c != 5 && unknown_4c != 6 && LinkedTo->unknown_slot108() > 0) {
            unknown_78 = -5;
            unknown_4c = 5;
            if (LinkedTo->Kind_Of() == 0xF) {
                ((InfantryClass *)LinkedTo)->unknown_slot311(0x22, false, false);
            }
        }
        switch (unknown_4c) {
        case 0:
            unknown_52fca0();
            break;
        case 1:
            unknown_52fd50();
            break;
        case 2:
            unknown_52fff0();
            break;
        case 3:
            unknown_530180();
            break;
        case 4:
            unknown_530550();
            break;
        case 5:
            unknown_530940();
            break;
        case 6:
            unknown_530ad0();
            break;
        }
        if (LinkedTo->unknown_77 && LinkedTo->House != unknown_player_a35db4) {
            if (Map.Unknown_00568140(Object_Coord(LinkedTo)) ||
                ((unknown_id_source_a3d290->unknown_000 & 0x1000) && Map.Unknown_005683C0(Object_Coord(LinkedTo)))) {
                LinkedTo->unknown_slot81();
            }
        }
        if (!LinkedTo->unknown_373 && LinkedTo->House != unknown_player_a35db4) {
            if (!Map.Unknown_00568140(Object_Coord(LinkedTo))) {
                LinkedTo->unknown_slot96(unknown_player_a35db4);
            }
        }
    }
    if (LinkedTo->unknown_7d && Layer() != layer) {
        Map.Submit(LinkedTo);
    }
    return false;
}
