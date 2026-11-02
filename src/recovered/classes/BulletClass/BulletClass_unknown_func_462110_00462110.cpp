// void BulletClass::unknown_func_462110(CoordStruct const &coord) (0x00462110)
// The detonation at coord (hypothesis: Westwood's BulletClass::Detonate):
// shakes the screen by the warhead's ranges, leaves the weapon's radiation
// in the cell (unknown_func_463720, expanded here), then applies the
// warhead's special: MindControl captures the target (springing its tag
// events 6 and 0x2C first, and playing YuriMindControlSound when a player's
// unit is involved), IvanBomb plants a bomb, ElectricAssault charges a
// building from an infantry owner, Parasite, Temporal, BombDisarm,
// MakesDisguise, NukeMaker (unknown_func_463c50); any other warhead fires
// the ShrapnelWeapon (unknown_func_462c50) and damages the area. Then the
// impact animation (scattered for Inviso), the combat light of a Bright
// bullet, and for an Airburst projectile nine AirburstWeapon bullets: one
// into each neighbour cell of the bullet's cell and one into the cell
// itself, each launched straight down with a random facing. A nullified
// hit (the area damage returned 2) shows Rules' WeaponNullifyAnim instead.
#include "shared/building_class.hpp"
#include "shared/unit.hpp"
#include "shared/infantry.hpp"
#include "shared/bullet.hpp"
#include "shared/bullet_type.hpp"
#include "shared/weapon_type.hpp"
#include "shared/warhead_type.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/radsite.hpp"
#include "shared/techno.hpp"
#include "shared/foot.hpp"
#include "shared/anim.hpp"
#include "shared/capture_manager.hpp"
#include "shared/parasite.hpp"
#include "shared/tag.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
#include "shared/random.hpp"
#include "shared/random2.hpp"
#include "shared/sound_play.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?Unknown_0047E2C0@@YIHABUCoordStruct@@HPAVTechnoClass@@PAVWarheadTypeClass@@_N@Z=0047e2c0
// @ref ?Unknown_0047F4D0@@YIPAVAnimTypeClass@@HPAVWarheadTypeClass@@HABUCoordStruct@@@Z=0047f4d0
// @ref ?Unknown_0047FCC0@@YGHUCoordStruct@@@Z=0047fcc0
// @ref ?Add_Bomb@UnknownList8322E0@@QAEXPAVTechnoClass@@PAVObjectClass@@@Z=00436470
// @ref ?Unknown_00607980@ParasiteClass@@QAEXPAVFootClass@@@Z=00607980
// @ref ?Unknown_006E27B0@UnknownTechno208@@QAEXPAVTechnoClass@@@Z=006e27b0
// @ref ?unknown_func_462c50@BulletClass@@QAEXXZ=00462c50
// @ref ?unknown_func_463c50@BulletClass@@QAEXXZ=00463c50

// The impact animation of a warhead hitting a land type (-1 above the
// ground) at a coordinate (0x0047F4D0, __fastcall; hypothesis).
AnimTypeClass *__fastcall Unknown_0047F4D0(int damage, WarheadTypeClass *warhead, int land, CoordStruct const &coord);
// The height adjustment an animation at a coordinate gets (0x0047FCC0;
// hypothesis: the AnimClass constructor's z adjustment).
int __stdcall Unknown_0047FCC0(CoordStruct coord);

// A value in [a, b] from the generator at 0x00839218 (the other generator's
// form of Random_Pick in shared/id_source.hpp: the result is a variable).
template<class T> inline T Random2_Pick(T a, T b)
{
    return T(unknown_random_839218((int)a, (int)b));
}

// The target as a techno (flag bit 0), or 0.
inline TechnoClass *Bullet_Target_Techno(AbstractClass *target)
{
    if (target == 0) return 0;
    return target->AbstractFlags.IsTechno ? static_cast<TechnoClass *>(target) : 0;
}

void BulletClass::unknown_func_462110(CoordStruct const &position)
{
    int damage_result = 1;
    bool special_impact = false;
    if (WH->ShakeXlo != 0 || WH->ShakeXhi != 0)
        Map.ShakeX = Random2_Pick(WH->ShakeXlo, WH->ShakeXhi);
    if (WH->ShakeYlo != 0 || WH->ShakeYhi != 0)
        Map.ShakeY = Random2_Pick(WH->ShakeYlo, WH->ShakeYhi);
    if (WeaponType != 0) {
        int level = WeaponType->unknown_12c;
        if (level > 0) {
            unknown_func_463720(Coord_Cell(position), (int)WeaponType->Warhead->CellSpread, level);
        }
    }
    if (WH->MindControl) {
        if (Owner != 0 && Owner->unknown_230 != 0) {
            ObjectClass *object = Target == 0 ? 0 :
                (Target->AbstractFlags.IsObject ? static_cast<ObjectClass *>(Target) : 0);
            bool target_house = Target != 0 && Target->AbstractFlags.IsTechno &&
                static_cast<TechnoClass *>(Target)->House->Unknown_004F52B0();
            if (object != 0 && object->unknown_7d && object->unknown_34 != 0) {
                object->unknown_34->Spring(6, object, unknown_geometry_k, false, (int)Owner);
                object->unknown_34->Spring(0x2c, object, unknown_geometry_k, false, (int)Owner);
            }
            if (static_cast<CaptureManagerClass *>(Owner->unknown_230)->Capture(static_cast<TechnoClass *>(Target))
                && Rules->YuriMindControlSound != -1
                && (Owner->House->Unknown_004F52B0() || target_house)) {
                Voc_Play_At(Rules->YuriMindControlSound, CoordStruct(object->Coord), 0);
            }
        }
    } else if (WH->IvanBomb) {
        TechnoClass *target = Target == 0 ? 0 :
            (Target->AbstractFlags.IsTechno ? static_cast<TechnoClass *>(Target) : 0);
        unknown_list_8322e0.Add_Bomb(Owner, target);
    } else if (WH->ElectricAssault) {
        if (Target != 0 && Target->Kind_Of() == 6 && Owner != 0 && Owner->Kind_Of() == 15)
            static_cast<BuildingClass *>(Target)->unknown_44da20(static_cast<InfantryClass *>(Owner));
    } else if (WH->Parasite) {
        if (Owner != 0) {
            FootClass *target = Target == 0 ? 0 :
                (Target->AbstractFlags.IsFoot ? static_cast<FootClass *>(Target) : 0);
            static_cast<FootClass *>(Owner)->unknown_588->Unknown_00607980(target);
        }
    } else if (WH->Temporal) {
        if (Owner != 0 && Target != 0) {
            TechnoClass *target = Bullet_Target_Techno(Target);
            Owner->unknown_208->Unknown_006E27B0(target);
        }
    } else if (WH->BombDisarm) {
        if (Target != 0 && Target->AbstractFlags.IsObject) {
            ObjectClass *object = static_cast<ObjectClass *>(Target);
            if (object->unknown_38 != 0) object->unknown_38->Unknown_00435FB0();
        }
    } else if (WH->MakesDisguise) {
        if (Owner != 0) Owner->unknown_slot255(static_cast<TechnoClass *>(Target));
    } else if (WH->NukeMaker) {
        unknown_func_463c50();
    } else {
        if (Type->ShrapnelWeapon != 0) unknown_func_462c50();
        int damage = DamageMultiplier * Strength;
        damage_result = Unknown_0047E2C0(position, damage >> 8, Owner, WH, true);
        if (!unknown_7d) return;
        if (damage_result == 2) special_impact = true;
    }
    CoordStruct impact = position;
    if (Type->Inviso) impact = Coord_Scatter(impact, 32, false);
    int land = -1;
    if (unknown_slot108() < unknown_level_height_850348 * 2) {
        land = Map[CoordStruct(Coord)].unknown_ec;
        if (land == 2 && damage_result == 0) {
            ObjectClass *occupier = Map[CoordStruct(Coord)].OccupierPtr;
            if (occupier != 0 && occupier->Kind_Of() == 1) {
                UnitTypeClass *type = static_cast<UnitClass *>(occupier)->Type;
                if (type->Naval && !type->Underwater) land = -1;
            }
        }
    }
    AnimTypeClass *animation = Unknown_0047F4D0(Strength, WH, land, CoordStruct(Coord));
    if (Bright && !special_impact) {
        unsigned flags = 0;
        if (WH->CLDisableRed) flags = 2;
        if (WH->CLDisableGreen) flags |= 4;
        if (WH->CLDisableBlue) flags |= 8;
        Unknown_0047F600(impact, Strength, WH, 1, flags);
    }
    if (special_impact) {
        AnimTypeClass *nullify = Rules->WeaponNullifyAnim;
        if (nullify != 0)
            new AnimClass(nullify, impact, 0, 1, 0x2600, Unknown_0047FCC0(impact));
    } else {
        if (animation != 0) {
            AnimClass *created = new AnimClass(animation, impact, 0, 1, 0x2600, Unknown_0047FCC0(impact));
            if (created == 0 && WH == Rules->unknown_c60) {
                int house_type = -1;
                if (Owner != 0) house_type = Owner->House->Type->House;
                Unknown_00422BA0(house_type, Coord_Cell(impact));
            }
        }
        if (Type->Airburst) {
            WeaponTypeClass *weapon = Type->AirburstWeapon;
            BulletTypeClass *projectile = weapon->Projectile;
            unsigned facing = 0;
            CellClass *center = static_cast<CellClass *>(unknown_slot105());
            int remaining = 8;
            do {
                CellClass &neighbor = center->Adjacent_Cell(facing);
                facing = (facing + 1) & 7;
                BulletClass *fragment = Create_Bullet(projectile, &neighbor, Owner, weapon->unknown_a4, weapon->Warhead, 50, false);
                if (fragment != 0) {
                    int random_direction = unknown_id_source_a3d290->Random()(0, 32);
                    short raw = (short)((unsigned short)(unsigned char)random_direction << 8);
                    double speed = (double)(weapon->unknown_a8 / 10);
                    double angle = ((int)raw - 0x3fff) * -9.587672516830327e-05;
                    BulletVelocityXY planar(unknown_cos_4ba4d0(angle) * unknown_cos_4ba4d0(4.712436918747274) * speed, unknown_sin_4ba480(angle) * unknown_cos_4ba4d0(4.712436918747274) * speed);
                    BulletVelocity velocity;
                    velocity.XY() = planar;
                    velocity.Z = unknown_sin_4ba480(4.712436918747274) * speed;
                    fragment->unknown_slot118(CoordStruct(Coord), velocity);
                }
            } while (--remaining != 0);
            BulletClass *fragment = Create_Bullet(projectile, center, Owner, weapon->unknown_a4, weapon->Warhead, 50, false);
            if (fragment != 0) {
                int random_direction = unknown_id_source_a3d290->Random()(0, 32);
                short raw = (short)((unsigned short)(unsigned char)random_direction << 8);
                double speed = (double)(weapon->unknown_a8 / 10);
                double angle = ((int)raw - 0x3fff) * -9.587672516830327e-05;
                BulletVelocityXY planar(unknown_cos_4ba4d0(angle) * unknown_cos_4ba4d0(4.712436918747274) * speed, unknown_sin_4ba480(angle) * unknown_cos_4ba4d0(4.712436918747274) * speed);
                BulletVelocity velocity;
                velocity.XY() = planar;
                velocity.Z = unknown_sin_4ba480(4.712436918747274) * speed;
                fragment->unknown_slot118(CoordStruct(Coord), velocity);
            }
        }
    }
}
