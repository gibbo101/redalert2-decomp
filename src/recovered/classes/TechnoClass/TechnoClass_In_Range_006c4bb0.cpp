// bool TechnoClass::unknown_6c4bb0(CoordStruct const *coord, AbstractClass *target, WeaponTypeClass *weapon) (0x006C4BB0):
// whether weapon fired from coord reaches target (TibSun TechnoTypeClass::In_Range, RA2 form with the range bonuses).
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"
#include "shared/rules.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
#include "shared/weapon_type.hpp"
#include "shared/building_class.hpp"
#include "shared/building_type_class.hpp"
#include "shared/combat.hpp"
#include "shared/fast_math.hpp"
#include "shared/unknown_geometry.hpp"

CellClass *__fastcall Find_First_Impenetrable_Obstacle_004bbaa0(CoordStruct const &from, CoordStruct const &to, WeaponTypeClass const *weapon, HouseClass const *house);

static inline int Distance_3D(CoordStruct const &a, CoordStruct const &b)
{
    CoordStruct delta = a - b;
    double y = delta.Y;
    double z = delta.Z;
    double x = delta.X;
    return (int)Fast_Sqrt(x * x + z * z + y * y);
}

static inline BuildingClass *As_Building(AbstractClass *target)
{
    if (target->Kind_Of() == 6) {
        return (BuildingClass *)target;
    }
    return 0;
}

static inline int Length_3D(CoordStruct const &delta)
{
    return (int)Fast_Sqrt((double)delta.X * delta.X + ((double)delta.Y * delta.Y + (double)delta.Z * delta.Z));
}

static inline int Length_XY(Point2D const &point)
{
    return (int)Fast_Sqrt((double)point.X * point.X + (double)point.Y * point.Y);
}

static inline Point2D Coord_XY(CoordStruct const &coord)
{
    return Point2D(coord.X, coord.Y);
}

static inline int Length_2D(CoordStruct const &coord)
{
    return (int)Fast_Sqrt((double)coord.X * coord.X + (double)coord.Y * coord.Y);
}

bool TechnoClass::unknown_6c4bb0(CoordStruct const *coord, AbstractClass *target, WeaponTypeClass *weapon)
{
    if (target != 0 && weapon != 0) {
        int range = weapon->unknown_b4;
        if (range == -512) {
            return true;
        }
        if (target->unknown_slot21()) {
            range += unknown_slot32()->AirRangeBonus;
        }
        BulletTypeClass *bullet = weapon->Projectile;
        int ground_range = range;
        if (bullet->SubjectToElevation) {
            ground_range = unknown_6c48f0((ObjectClass *)target) + range;
        }
        CoordStruct tcoord = target->Center_Coord();
        int minrange = weapon->unknown_b8;
        if (minrange != 0 && Distance_3D(*coord, tcoord) < minrange) {
            return false;
        }
        if (bullet->Arcing) {
            CoordStruct delta = tcoord - *coord;
            int dist = Length_XY(Coord_XY(delta));
            int arcrange = range;
            if (bullet->SubjectToElevation) {
                arcrange = unknown_6c4a70((ObjectClass *)target) + range;
            }
            if (dist > arcrange) {
                return false;
            }
            double gravity = weapon->Projectile->Floater ? Unknown_0047FCD0() : Rules->unknown_1320;
            int speed = Unknown_0047FB70(arcrange, gravity);
            if (!Is_Projectile_Trajectory_Valid(speed, dist, delta.Z, gravity)) {
                return false;
            }
            if ((Map[tcoord].unknown_140 & 0x100) && tcoord.Z - coord->Z >= unknown_geometry_g * 3) {
                return false;
            }
            bool clear = Find_First_Impenetrable_Obstacle_004bbaa0(*coord, tcoord, weapon, House) == 0;
                return clear;
        } else {
            BuildingClass *building = As_Building(target);
            if (building != 0) {
                ground_range += (building->Type->Foundation_Height(false) + building->Type->Width()) * 64;
            }
            bool inrange;
            if (Kind_Of() != 3) {
                inrange = Length_3D(*coord - tcoord) <= ground_range;
            } else {
                inrange = Length_XY(Coord_XY(*coord) - Coord_XY(tcoord)) <= ground_range;
            }
            if (inrange) {
                if (Map[*coord].unknown_140 & 0x100) {
                    int height = Map.Unknown_0055A280(*coord) + unknown_geometry_j;
                    if (coord->Z < height && tcoord.Z >= height) {
                        return false;
                    }
                }
                bool clear = Find_First_Impenetrable_Obstacle_004bbaa0(*coord, tcoord, weapon, House) == 0;
                return clear;
            }
        }
    }
    return false;
}
