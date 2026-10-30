// bool __stdcall DropPodLocomotionClass::Process() (0x004A5B00, ILocomotion 16)
// TibSun DropPod.cpp Process: the pod falls at DropPodAngle (X toward the chosen side)
// at least DropPodSpeed; on the ground the object is unlimboed (or destroyed with a C4
// explosion when that fails) and the piggybacked locomotor restored; in the air every
// sixth frame leaves SMOKEY and every third the DropPodWeapon strafes near the target.
// The body runs to 0x004A5FBB (Ghidra splits it at 0x004A5F5A/0x004A5F70).
#include "shared/droppod_locomotion.hpp"
#include "shared/foot.hpp"
#include "shared/rules.hpp"
#include "shared/anim.hpp"
#include "shared/anim_type.hpp"
#include "shared/infantry.hpp"
#include "shared/bullet.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/house.hpp"
#include "shared/weapon_type.hpp"
#include "shared/sound_play.hpp"
// @ref ??_C@_06NHJA@SMOKEY?$AA@=007d5fe8

bool __stdcall DropPodLocomotionClass::Process()
{
    CoordStruct coord = LinkedTo->Coord;
    CoordStruct smoke = coord;
    int speed = LinkedTo->unknown_slot108() / 10 + 2;
    if (Rules->DropPodSpeed > speed) {
        speed = Rules->DropPodSpeed;
    }
    if (unknown_1c) {
        coord.X += unknown_cos_4ba4d0(Rules->DropPodAngle) * speed;
    } else {
        coord.X -= unknown_cos_4ba4d0(Rules->DropPodAngle) * speed;
    }
    coord.Z -= unknown_sin_4ba480(Rules->DropPodAngle) * speed;
    int height = LinkedTo->unknown_slot108();
    FootClass *linked = LinkedTo;
    if (height <= 0) {
        linked->unknown_slot109(0);
        coord = linked->Coord;
        linked->unknown_slot52();
        AddRef();
        UnknownComPtr<ILocomotion, &unknown_uuid_ILocomotion_7ce600> &locomotor = LinkedTo->Locomotor;
        locomotor.Attach(0);
        End_Piggyback(&locomotor.Pointer);
        if (!linked->unknown_slot53(&coord, 0)) {
            Unknown_0047E2C0(coord, 100, LinkedTo, Rules->unknown_c74, true);
            new AnimClass(Select_Damage_Anim(100, Rules->unknown_c74, 0, &coord), coord, 0, 1, 0x2600, Unknown_0047FCC0(coord));
        } else {
            new AnimClass(Rules->DropPodPuff, coord, 0, 1, 0x600, 0);
            if (unknown_1c) {
                new AnimClass(Rules->DropPod[1], coord, 0, 1, 0x600, 0);
            } else {
                new AnimClass(Rules->DropPod[0], coord, 0, 1, 0x600, 0);
            }
            linked->unknown_slot71(1);
            linked->unknown_slot109(0);
            linked->unknown_slot261(false, true);
            linked->unknown_slot117();
            linked->unknown_slot87(unknown_coord_852a20, false, false);
        }
        Release();
    } else {
        linked->unknown_slot103(coord);
        WeaponTypeClass *weapon = Rules->DropPodWeapon;
        if (weapon != 0) {
            if (Frame % 6 == 0) {
                new AnimClass(AnimTypes[AnimTypeClass::From_Name("SMOKEY")], smoke, 0, 1, 0x600, 0);
            }
            if (Frame % 3 == 0) {
                if (!LinkedTo->House->Is_Ally((TechnoClass *)Map[unknown_20].unknown_471660(Point2D(0, 0), false, 0))) {
                    CoordStruct scattered = Coord_Scatter(unknown_20, 0x55, false);
                    Voc_Play_At(weapon->unknown_bc.Pick(unknown_random_839218()), coord, 0);
                    Unknown_0047E2C0(scattered, weapon->unknown_a4 * 2, LinkedTo, weapon->Warhead, true);
                    new AnimClass(Select_Damage_Anim(weapon->unknown_a4 * 2, weapon->Warhead, 0, &scattered), scattered, 0, 1, 0x2600, Unknown_0047FCC0(scattered));
                }
            }
        }
    }
    return true;
}
