// int FootClass::unknown_slot145() (0x004C3950, slot 145)
// The patrol mission (TibSun Do_MISSION_PATROL shape; the switch on the
// mission status +0xA8 ends in a four-entry jump table 0x004C41D0). The scan
// distance is the threat range (slot 188, mode 2) in cells plus 6; +0x37F is
// set. 3: waits for a destination (+0x494), then 0. 0: takes the greatest
// threat around the unit (slot 219 mode 2); an object in range of its weapon
// (slots 174, 212) or within the walk distance (0x0042AA30) becomes the
// target: the patrol cell (+0x4CC) is the target cell (slot 107), moved to a
// nearby cell (0x005502E0) when it is a bridge cell and the unit is not
// moving onto a bridge (60 when none); the archive target (+0x1B0, through
// 0x006D6E50) becomes the last queued destination (+0x478), the destination
// or the patrol cell; status 1. Without one, a unit that is not moving goes
// idle (slot 261) with status 3. 1: a renovator (slot 193) drops an allied
// building above ConditionRed; a target in reach is approached (slot 304)
// and, once gone, the unit heads back to the archive target with status 0
// (45). Otherwise a new threat around the patrol cell is taken (1), or the
// unit heads to the closer of the patrol cell and the archive target with
// status 2, or goes idle. 2: a threat around the patrol cell is taken
// (status 1); without a destination the unit heads to the archive target
// (status 0) or goes idle. Returns the mission delay plus 0..2.
#include "shared/foot.hpp"
#include "shared/map_view.hpp"
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
#include "shared/rules.hpp"
#include "shared/path_estimator.hpp"
#include "shared/id_source.hpp"
#include "shared/unknown_geometry.hpp"
// @ref _unknown_geometry_k=00865f00
// @ref __real@8@4008e100000000000000=0079b608
// @ref ?unknown_6d6e50@TechnoClass@@QAEXPAVAbstractClass@@@Z=006d6e50
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290

int FootClass::unknown_slot145()
{
    int trange = unknown_slot188(2);
    unknown_37f = true;
    int dist = trange / 256 + 6;

    switch (unknown_a8) {
    case 3:
        if (unknown_494 != 0) {
            unknown_a8 = 0;
            return 1;
        }
        break;

    case 0: {
        CoordStruct coord = Coord;
        AbstractClass *target = unknown_slot219(2, &coord, false);
        ObjectClass *optr = target == 0 ? 0 : (target->AbstractFlags.IsObject ? (ObjectClass *)target : 0);
        int primary = unknown_slot174(optr);

        if (optr != 0 && (unknown_slot212(optr, primary) || unknown_path_estimator_8315c8.Unknown_0042AA30(Coord_Cell(unknown_slot19(0)), Coord_Cell(optr->unknown_slot19(0)), this, unknown_slot46(0), optr->unknown_slot46(0), -1) < dist)) {
            unknown_4cc = (AbstractClass *)unknown_slot107();
            if ((((UnknownCellClass *)unknown_4cc)->Flags & 0x100) && !unknown_slot46(0)) {
                Cell cell = Map.Unknown_005502E0(((UnknownCellClass *)unknown_4cc)->unknown_24, unknown_slot32()->SpeedType, Map.Zone(((UnknownCellClass *)unknown_4cc)->unknown_24, unknown_slot32()->MovementZone, false), unknown_slot32()->MovementZone, false, Point2D(1, 1), 0, 1, 0, 0, Cell(0, 0), 0);
                if (cell != unknown_geometry_k) {
                    unknown_4cc = (AbstractClass *)&Map[cell];
                } else {
                    unknown_4cc = 0;
                    return 60;
                }
            }

            if (unknown_1b0 == 0) {
                if (unknown_478.Count() > 0) {
                    unknown_6d6e50(unknown_478[unknown_478.Count() - 1]);
                } else if (unknown_494 != 0) {
                    unknown_6d6e50(unknown_494);
                } else {
                    unknown_6d6e50(unknown_4cc);
                }
            }

            unknown_slot260(0, 1);
            unknown_slot220(target);
            unknown_a8 = 1;

        } else if (unknown_494 == 0 || !Locomotor.Checked()->Is_Moving()) {
            unknown_slot261(false, true);
            unknown_a8 = 3;
            return 1;
        }
        break;
    }

    case 1: {
        ObjectClass *optr = unknown_228 == 0 ? 0 : (unknown_228->AbstractFlags.IsObject ? (ObjectClass *)unknown_228 : 0);
        int primary = unknown_slot174(optr);

        if (unknown_slot193() && optr != 0 && optr->Kind_Of() == 6 && House->Is_Ally(((TechnoClass *)optr)->House) && optr->Health_Ratio() > Rules->unknown_1370) {
            unknown_slot220(0);
        } else if (optr != 0 && (unknown_slot212(optr, primary) || unknown_path_estimator_8315c8.Unknown_0042AA30(((UnknownCellClass *)unknown_4cc)->unknown_24, Coord_Cell(optr->unknown_slot19(0)), this, ((UnknownCellClass *)unknown_4cc)->Flags >> 8 & 1, optr->unknown_slot46(0), -1) < dist)) {
            unknown_slot304();
            if (unknown_228 != 0) {
                break;
            }
            unknown_slot260(unknown_1b0, 1);
            unknown_6d6e50(0);
            unknown_4cc = 0;
            unknown_a8 = 0;
            return 45;
        }

        if (unknown_228 == 0) {
            AbstractClass *target = unknown_slot219(2, &unknown_4cc->Center_Coord(), false);
            ObjectClass *scan = target == 0 ? 0 : (target->AbstractFlags.IsObject ? (ObjectClass *)target : 0);
            int weapon = unknown_slot174(scan);
            if (scan != 0 && (unknown_slot212(scan, weapon) || unknown_path_estimator_8315c8.Unknown_0042AA30(((UnknownCellClass *)unknown_4cc)->unknown_24, Coord_Cell(scan->unknown_slot19(0)), this, ((UnknownCellClass *)unknown_4cc)->Flags >> 8 & 1, scan->unknown_slot46(0), -1) < dist)) {
                unknown_slot220(target);
                unknown_slot260(0, 1);
                return 1;
            }
        }

        unknown_a8 = 2;
        unknown_slot220(0);
        if (unknown_1b0 != 0) {
            UnknownCellClass *tcell = (UnknownCellClass *)unknown_slot107();
            bool onbridge = unknown_slot46(0);
            UnknownCellClass *acell = (UnknownCellClass *)&Map[unknown_1b0->Center_Coord()];
            int patrolwalk = unknown_path_estimator_8315c8.Unknown_0042AA30(tcell->unknown_24, ((UnknownCellClass *)unknown_4cc)->unknown_24, this, onbridge, ((UnknownCellClass *)unknown_4cc)->Flags >> 8 & 1, -1);
            if (patrolwalk < unknown_path_estimator_8315c8.Unknown_0042AA30(tcell->unknown_24, acell->unknown_24, this, onbridge, acell->Flags >> 8 & 1, -1)) {
                unknown_slot260(unknown_4cc, 1);
            } else {
                unknown_slot260(unknown_1b0, 1);
            }
            return 1;
        }
        unknown_a8 = 0;
        unknown_slot261(false, true);
        unknown_a8 = 3;
        return 1;
    }

    case 2: {
        AbstractClass *target = unknown_slot219(2, &unknown_4cc->Center_Coord(), false);
        ObjectClass *optr = target == 0 ? 0 : (target->AbstractFlags.IsObject ? (ObjectClass *)target : 0);
        int primary = unknown_slot174(optr);

        if (optr != 0 && (unknown_slot212(optr, primary) || unknown_path_estimator_8315c8.Unknown_0042AA30(((UnknownCellClass *)unknown_4cc)->unknown_24, Coord_Cell(optr->unknown_slot19(0)), this, ((UnknownCellClass *)unknown_4cc)->Flags >> 8 & 1, optr->unknown_slot46(0), -1) < dist)) {
            unknown_slot220(target);
            unknown_slot260(0, 1);
            unknown_a8 = 1;
            break;
        }

        if (unknown_494 == 0) {
            unknown_slot220(0);
            if (unknown_1b0 != 0) {
                unknown_slot260(unknown_1b0, 1);
                unknown_6d6e50(0);
                unknown_a8 = 0;
                unknown_4cc = 0;
            } else {
                unknown_a8 = 0;
                unknown_slot261(false, true);
                unknown_a8 = 3;
                return 1;
            }
        }
        break;
    }

    default:
        break;
    }

    int delay = (int)(Control()->unknown_10 * 900.0);
    return delay + unknown_id_source_a3d290->Random()(0, 2);
}
