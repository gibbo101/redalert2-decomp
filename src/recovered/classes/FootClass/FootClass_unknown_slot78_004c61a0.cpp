// bool FootClass::unknown_slot78(int action, int arg2, bool arg3) (0x004C61A0, slot 78)
// Carries out a click on an object (arg2 is the ObjectClass pointer; arg3
// set for waypoint orders, which ignore the 0x00A40BA4/0x00A40BA8 keys):
// queues the order through slot 200 by action. Guard area (26) sabotages an
// enemy building instead when this is C4 infantry or has ability 14; 55
// queues an event (10) for the owner; a move (1, 62, and 2 when the
// object's cell is visible or the type may move to shroud) looks for a
// nearby reachable cell when the object's zone differs, then moves with the
// object's cell as the second target. 59 guards (area when the first weapon
// heals). TibSun Active_Click_With(ObjectClass *) shape: successes return
// true, failures break to the shared return false.
#include "shared/foot.hpp"
#include "shared/map_view.hpp"
#include "shared/techno_type.hpp"
#include "shared/infantry.hpp"
#include "shared/infantry_type.hpp"
#include "shared/house.hpp"
#include "shared/event.hpp"
#include "shared/target.hpp"
#include "shared/rules.hpp"
#include "shared/keyboard.hpp"
#include "shared/weapon_type.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ??0TargetClass@@QAE@PAVAbstractClass@@@Z=006b54a0
// @ref ??0EventClass@@QAE@HHVTargetClass@@@Z=004b5ef0
// @ref ?OutList@@3V?$QueueClass@VEventClass@@$0IA@@@A=00a32338
// @ref __imp__timeGetTime@0=0079a524
// @ref _unknown_geometry_k=00865f00

// A key binding is down (the bindings are ints; WWKeyboardClass takes 16-bit keys).
inline bool Foot_Key_Down(int key) { return WWKeyboard->Down(key); }

bool FootClass::unknown_slot78(int action, int arg2, bool arg3)
{
    ObjectClass *object = (ObjectClass *)arg2;

    switch (action) {
    case 26:
        if (unknown_slot38() && unknown_slot39()) {
            if (((Kind_Of() == 15 && ((InfantryClass *)this)->Type->C4) || unknown_6d7910(14))
                && object->Kind_Of() == 6 && !House->Is_Ally((TechnoClass const *)object)) {
                unknown_slot200(0x11, 0, (int)object, 0);
            } else {
                unknown_slot200(0xB, object, 0, 0);
            }
            return true;
        }
        break;

    case 4:
    case 52:
    case 56:
        unknown_slot200(0x10, 0, 0, 0);
        return true;

    case 55:
        OutList.Add(EventClass(unknown_38->unknown_28->ArrayIndex, 10, TargetClass(this)));
        return true;

    case 5:
    case 53:
    case 63:
    case 64:
        if (unknown_slot38()) {
            unknown_slot200(1, object, 0, 0);
            return true;
        }
        break;

    case 3:
        if (unknown_slot39() && object && object->As_Techno()) {
            unknown_slot200(7, 0, (int)object, 0);
            return true;
        }
        break;

    case 9:
        if (unknown_slot39()) {
            unknown_slot200(8, 0, (int)object, 0);
            return true;
        }
        break;

    case 11:
        if (unknown_slot39()) {
            unknown_slot200(9, 0, (int)object, 0);
            return true;
        }
        break;

    case 16:
        if (unknown_slot39()) {
            unknown_slot200(0x11, 0, (int)object, 0);
            return true;
        }
        break;

    case 2:
        if (Map.Unknown_00568140(object->Center_Coord()) && !unknown_slot32()->MoveToShroud) {
            return false;
        }
        // Fall into next case.

    case 1:
    case 62:
        if (unknown_slot39()) {
            AbstractClass *targ = object;

            CoordStruct center = object->Center_Coord();
            if (center.Z <= Map.Unknown_0055A280(center)) {
                center.Z = Map.Unknown_0055A280(center);
            }

            if (((unknown_slot32()->unknown_af5 && !Rules->AllowShroudedSubteranneanMoves) || Kind_Of() == 2) && Map.Unknown_00568140(center)) return true;

            int mzone = unknown_slot32()->MovementZone;
            Cell cell = Coord_Cell(object->unknown_slot19(0));
            bool in_radar = Map.Unknown_0055A660(cell, true);
            UnknownCellClass *cptr = (UnknownCellClass *)&Map[unknown_slot19(0)];

            if (mzone == 6) mzone = 0;
            else if (mzone == 9) mzone = 7;

            bool moveanywhere = unknown_slot21() || unknown_slot32()->unknown_af5 || (Kind_Of() == 15 && ((InfantryClass *)this)->Type->JumpJet) || Kind_Of() == 2;

            bool ontobridge = unknown_slot46(0);
            CoordStruct coord = Cell_Coord(cell);
            coord.Z = Map.Unknown_0055A280(coord);
            bool shrouded = Map.Unknown_00568140(coord);
            bool forcemove = !arg3 && (Foot_Key_Down(unknown_key_a40ba4) || Foot_Key_Down(unknown_key_a40ba8));

            if (moveanywhere && action == 2) {
                Cell nearby = Map.Unknown_005502E0(cell, unknown_slot32()->SpeedType, -1, mzone, ((UnknownCellClass *)&Map[cell])->Flags >> 8 & 1, Point2D(1, 1), 0, 1, unknown_slot32()->unknown_af5 && unknown_slot108() < 0, 1, Cell(0, 0), 0);
                if (nearby != unknown_geometry_k) {
                    targ = &Map[nearby];
                }
            } else {
                if (!in_radar || !moveanywhere && (shrouded || action == 2 || forcemove && Kind_Of() == 15 || !Map.Unknown_0054F7C0(cptr->unknown_24, cell, mzone, ontobridge, ((UnknownCellClass *)&Map[cell])->Flags >> 8 & 1, false))) {
                    Cell nearby = Map.Unknown_005502E0(cell, unknown_slot32()->SpeedType, Map.Zone(cptr->unknown_24, mzone, ontobridge), mzone, ((UnknownCellClass *)&Map[cell])->Flags >> 8 & 1, Point2D(1, 1), 0, 1, 0, 1, Cell(0, 0), 0);
                    if (nearby != unknown_geometry_k) {
                        targ = &Map[nearby];
                    }
                }
            }

            if (targ != 0) {
                CellClass *from = 0;
                if (targ != object && object != 0) {
                    from = &Map[Coord_Cell(object->Center_Coord())];
                }
                unknown_slot200(2, 0, (int)targ, (int)from);
            }
            return true;
        }
        break;

    case 51:
    case 54:
        return false;

    case 59: {
        WeaponStruct *weapon = unknown_slot231(0);
        bool heals = (weapon != 0 && weapon->WeaponType != 0 && weapon->WeaponType->unknown_a4 < 0);
        unknown_slot200(heals ? 0xB : 5, this, 0, 0);
        return true;
    }

    default:
        return true;
    }
    return false;
}
