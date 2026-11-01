// bool __stdcall TeleportLocomotionClass::Process() (0x006E0E10, ILocomotion 10)
// The chrono warp, staged by +0x38. A pending warp (+0x205) waits on the
// timer (slot 10); a warp the object queued (+0x214) becomes the stage.
// Stage 0 while moving to a fresh destination: targets on the object are
// dropped (0x006D7C80, bullets aimed at it), WarpOut plays, the delay
// timer is set from the distance (ChronoTrigger / ChronoDistanceFactor,
// at least ChronoMinimumDelay; harvesters jump at once), the object is
// taken off the map, moved to +0x28 (on a bridge there or not) and put
// back, with the chrono out and in sounds. An object flagged +0x210 runs
// stages 1-7 instead: warp out (2), clear the arrival cell (3: 0x006DFF00,
// ChronoDelay into +0x218), arrive (4), crush the arrival cell's occupants
// (5: 0x006E0430) and finish (7).
#include "shared/teleport_locomotion.hpp"
#include "shared/cell.hpp"
#include "shared/rules.hpp"
#include "shared/techno_type.hpp"
#include "shared/bullet.hpp"
#include "shared/anim.hpp"
#include "shared/sound_play.hpp"
#include "shared/coord_distance.hpp"
#include "shared/parasite.hpp"
// @ref ?unknown_coord_ac0280@@3UCoordStruct@@A=00ac0280
// @ref ?Unknown_00607440@ParasiteClass@@QAEXXZ=00607440

bool __stdcall TeleportLocomotionClass::Process()
{
    int distance = 0;
    if (LinkedTo->unknown_205 && unknown_38 == 0 && LinkedTo->unknown_214 == 0) {
        unknown_slot10();
        return false;
    }
    if (unknown_38 == 0 && LinkedTo->unknown_214 != 0) {
        unknown_38 = LinkedTo->unknown_214;
        return false;
    }
    if (!LinkedTo->unknown_210) {
        if (unknown_38 <= 0) {
            if (Is_Moving()) {
                if (Object_Coord(LinkedTo) != unknown_28 && unknown_28 != unknown_coord_ac0280) {
                    Unknown_006D7C80(LinkedTo);
                    for (int index = unknown_BulletClass_list_00a40ce8.Count() - 1; index >= 0; index--) {
                        BulletClass *bullet = unknown_BulletClass_list_00a40ce8[index];
                        if (bullet->Target == LinkedTo) {
                            bullet->unknown_func_461470();
                        }
                    }
                    new AnimClass(Rules->WarpOut, Object_Coord(LinkedTo), 0, 1, 0x600, 0);
                    distance = Coord_Distance(LinkedTo->Center_Coord(), unknown_28);
                    unknown_3c = 0;
                    if (Rules->ChronoTrigger) {
                        unknown_3c = distance / Rules->ChronoDistanceFactor;
                    }
                    unknown_3c = unknown_3c > Rules->ChronoMinimumDelay ? unknown_3c : CDTimerClass<FrameTimerClass>(Rules->ChronoMinimumDelay);
                    if (distance < Rules->ChronoRangeMinimum) {
                        unknown_3c = Rules->ChronoMinimumDelay;
                    }
                    LinkedTo->unknown_205 = true;
                    if (LinkedTo->Kind_Of() == 1 && ((UnitClass *)LinkedTo)->Type->Harvester) {
                        unknown_3c = 0;
                        LinkedTo->unknown_205 = false;
                    }
                    if (LinkedTo->unknown_580 != 0) {
                        LinkedTo->unknown_580->unknown_588->Unknown_00607440();
                    }
                    LinkedTo->unknown_slot71(0);
                    {
                        FootClass *linked = LinkedTo;
                        int sound = linked->unknown_slot32()->ChronoOutSound;
                        if (sound != -1 || (sound = Rules->ChronoOutSound) != -1) {
                            Voc_Play_At(sound, Object_Coord(linked), 0);
                        }
                    }
                    LinkedTo->unknown_slot103(unknown_28);
                    Cell where = Coord_Cell(unknown_28);
                    CellClass *cell = &Map[where];
                    LinkedTo->unknown_slot103(unknown_28);
                    if (cell->unknown_140 & 0x100) {
                        LinkedTo->unknown_79 = true;
                    } else {
                        LinkedTo->unknown_79 = false;
                    }
                    LinkedTo->unknown_slot109(0);
                    LinkedTo->unknown_slot71(1);
                    {
                        FootClass *linked = LinkedTo;
                        int sound = linked->unknown_slot32()->ChronoInSound;
                        if (sound != -1 || (sound = Rules->ChronoInSound) != -1) {
                            Voc_Play_At(sound, Object_Coord(linked), 0);
                        }
                    }
                    LinkedTo->unknown_slot93(2);
                    Stop_Moving();
                    cell->unknown_476cc0(LinkedTo);
                    LinkedTo->unknown_slot260(0, 1);
                    new AnimClass(Rules->WarpOut, Object_Coord(LinkedTo), 0, 1, 0x600, 0);
                    LinkedTo->unknown_214 = 0;
                    return false;
                }
                LinkedTo->unknown_slot260(0, 1);
                Stop_Moving();
                return false;
            }
            return false;
        }
    } else if (unknown_38 == 0) {
        LinkedTo->unknown_204 = true;
        unknown_3c = 60;
        unknown_38++;
        return false;
    }
    if (unknown_38 == 1) {
        unknown_slot10();
        return false;
    }
    if (unknown_38 == 2) {
        new AnimClass(Rules->WarpOut, Object_Coord(LinkedTo), 0, 1, 0x600, 0);
        LinkedTo->unknown_slot71(0);
        {
            FootClass *linked = LinkedTo;
            int sound = linked->unknown_slot32()->ChronoOutSound;
            if (sound != -1 || (sound = Rules->ChronoOutSound) != -1) {
                Voc_Play_At(sound, Object_Coord(linked), 0);
            }
        }
        LinkedTo->unknown_205 = true;
        LinkedTo->unknown_210 = false;
        LinkedTo->unknown_204 = false;
        LinkedTo->unknown_79 = false;
        bool ok = unknown_6dff00(LinkedTo->unknown_21c, false);
        unknown_38++;
        if (ok) {
            unknown_38++;
            return false;
        }
        return false;
    }
    if (unknown_38 == 3) {
        if (unknown_6dff00(LinkedTo->unknown_21c, false)) {
            unknown_38++;
        }
        LinkedTo->unknown_218 = Rules->ChronoDelay;
        return false;
    }
    if (unknown_38 == 4) {
        unknown_6dff00(LinkedTo->unknown_21c, true);
        LinkedTo->unknown_slot103(unknown_28);
        LinkedTo->unknown_slot109(0);
        LinkedTo->unknown_slot71(1);
        unknown_38++;
        return false;
    }
    if (unknown_38 == 5) {
        LinkedTo->unknown_slot103(unknown_28);
        LinkedTo->unknown_slot109(0);
        LinkedTo->unknown_slot71(1);
        {
            FootClass *linked = LinkedTo;
            int sound = linked->unknown_slot32()->ChronoInSound;
            if (sound != -1 || (sound = Rules->ChronoInSound) != -1) {
                Voc_Play_At(sound, Object_Coord(linked), 0);
            }
        }
        if (!Map.Unknown_0055A660(LinkedTo->unknown_slot104(), true)) {
            LinkedTo->unknown_32d = false;
        }
        if (LinkedTo->unknown_214 == 0) {
            unknown_6e0430(unknown_28);
        }
        if (LinkedTo->unknown_7d) {
            LinkedTo->unknown_slot93(2);
            Stop_Moving();
            LinkedTo->unknown_6d6e50(0);
            LinkedTo->unknown_slot260(0, 1);
            unknown_3c = LinkedTo->unknown_218;
            new AnimClass(Rules->WarpOut, Object_Coord(LinkedTo), 0, 1, 0x600, 0);
            unknown_38++;
            return false;
        }
        return false;
    }
    if (unknown_38 == 6) {
        unknown_slot10();
        return false;
    }
    if (unknown_38 == 7) {
        LinkedTo->unknown_205 = false;
        LinkedTo->unknown_6d6e50(0);
        LinkedTo->unknown_slot260(0, 1);
        unknown_34 = false;
        LinkedTo->unknown_214 = 0;
        unknown_38 = 0;
    }
    return false;
}
