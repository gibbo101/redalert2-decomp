// Completes animation sequences and returns to locomotion/idle (0x005078B0).
// Sequence 27 continues with 28 and 34 with 35; 11-15 leave a corpse animation
// (the type's DeadBodies, else Rules' for humans) and remove the object; 31 and
// unlisted sequences pick the next idle/move sequence. Case 31 and the default's
// last arm compile to one block (cross-jumped).
#include "shared/infantry.hpp"
#include "shared/anim.hpp"
#include "shared/rules.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref ??0AnimClass@@QAE@PBVAnimTypeClass@@ABUCoordStruct@@HHHH@Z=00420110
// @ref ??2@YAPAXI@Z=00782017
// @ref ?Set_Current@FacingClass@@QAEXABUUnknownFacingDir@@@Z=004b8b10
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?unknown_6d96a0@TechnoClass@@QAEXXZ=006d96a0
inline AnimTypeClass *Pick_Animation(TypeList<AnimTypeClass *> const &list, unsigned draw)
{
    return list[draw % list.Count()];
}
// A corpse animation is chosen after allocation, with one scenario draw.
inline AnimTypeClass *InfantryClass::Pick_Dead_Body(bool use_type) const
{
    unsigned draw = (unsigned)unknown_id_source_a3d290->Random()();
    if (use_type) {
        return Pick_Animation(Type->DeadBodies, draw);
    }
    return Pick_Animation(Rules->DeadBodies, draw);
}
void InfantryClass::Advance_Animation_005078b0()
{
    if (Sequence == -1 || StageClass::Stage >= Type->DoControls[Sequence].Count) {
        switch (Sequence) {
        case 27:
            unknown_slot311(28, true, false);
            unknown_6d96a0();
            break;
        case 31:
            unknown_slot311(0, true, false);
            break;
        default:
            if (Sequence != -1) {
                int facing = Type->DoControls[Sequence].Facing;
                if (facing != -1) {
                    UnknownFacingDir direction((unsigned short)(facing << 13));
                    unknown_2e0.Set_Current(direction);
                }
            }
            if (Locomotor.Checked()->Is_Moving() && unknown_468 > 0.1) {
                if (unknown_5c3) {
                    unknown_slot311(6, true, false);
                } else {
                    unknown_slot311(3, true, false);
                }
            } else {
                if (unknown_5090d0()) {
                    unknown_slot311(28, true, false);
                } else if (unknown_5c3) {
                    unknown_slot311(2, true, false);
                } else {
                    unknown_slot311(0, true, false);
                }
            }
            break;
        case 34:
            unknown_slot311(35, true, false);
            break;
        case 11: case 12: case 13: case 14: case 15:
            if (StageClass::Stage >= Type->DoControls[Sequence].Count) {
                if (Type->DeadBodies.Count() > 0) {
                    new AnimClass(Pick_Dead_Body(true),
                        Center_Coord(), 0, 1, 0x600, 0);
                } else if (!Type->NotHuman) {
                    new AnimClass(Pick_Dead_Body(false),
                        Center_Coord(), 0, 1, 0x600, 0);
                }
                unknown_slot60();
            }
            break;
        case 20: case 21: case 36:
            if (StageClass::Stage >= Type->DoControls[Sequence].Count) {
                unknown_slot60();
            }
            break;
        case 33:
            break;
        }
    }
    if (Sequence == 33 && !unknown_7a) {
        unknown_slot311(0, true, false);
    }
}
