// void BulletClass::unknown_func_461de0(bool forced) (0x00461DE0)
// See shared/bullet.hpp. The aim point starts at the bullet; an accurate
// bullet close to its target (within 32) takes the target's centre, and
// unless its warhead is an EMP or it bursts in the air, the remembered point
// (Data +0x18) of a straight, unforced shot, an object target's slot 40
// point (within 0x80) or a target's slot 22 point (within 0x2A; a building
// whose type has an offset at +0xC48 uses slot 40). Then Cluster
// detonations (0x00462110), the later ones scattered 256-511 leptons around
// the aim point, until the bullet is gone; an air burst detonates once.
#include "shared/bullet.hpp"
#include "shared/bullet_type.hpp"
#include "shared/warhead_type.hpp"
#include "shared/building_type.hpp"
#include "shared/unknown_vector3.hpp"
#include "shared/random.hpp"
// @ref ??0UnknownVector3@@QAE@HHH@Z=0041b630
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref ?unknown_5d4c00@ObjectClass@@QAEHPAVAbstractClass@@@Z=005d4c00
// @ref ?unknown_func_462110@BulletClass@@QAEXABUCoordStruct@@@Z=00462110
// @ref ?Coord_Scatter@@YI?AUCoordStruct@@ABU1@H_N@Z=00491750
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0

// A target building as this function reads it (BuildingClass +0x418 Type).
struct UnknownBulletTargetBuilding {
    char unknown_000[0x418];
    BuildingTypeClass *Type;            // +0x418
};

// The length of an offset taken by value (the terms loaded Y, Z, X and
// summed X, Z, Y, as foot.hpp's Offset_Length).
inline UnknownVector3 Coord_Offset(CoordStruct const &from, CoordStruct const &to)
{
    return UnknownVector3(from.X - to.X, from.Y - to.Y, from.Z - to.Z);
}

inline int Vector_Length(UnknownVector3 vector)
{
    double y = vector.Y;
    double z = vector.Z;
    double x = vector.X;
    return (int)unknown_sqrt_4ba410(x * x + z * z + y * y);
}

void BulletClass::unknown_func_461de0(bool forced)
{
    ObjectClass *object = 0;
    CoordStruct coord = Coord;
    if (Target != 0 && Target->unknown_slot21()) {
        object = (ObjectClass *)Target;
    }
    if (!Type->Inaccurate) {
        if (Target != 0) {
            if (Vector_Length(Coord_Offset(coord, Target->Center_Coord())) < 32
                && !Type->Airburst && !Type->Inaccurate) {
                coord = Target->Center_Coord();
            }
        }
        if (!WH->EMEffect && !Type->Airburst) {
            if (!forced && !Type->Arcing && Type->ROT <= 0) {
                CoordStruct aim = Data.unknown_18;
                if (aim != unknown_geometry_l) {
                    coord = Data.unknown_18;
                }
            }
            if (object != 0 && object->unknown_slot29() != 2) {
                if (unknown_5d4c00(Target) < 0x80) {
                    coord = object->unknown_slot40();
                }
            } else if (Target != 0 && unknown_5d4c00(Target) < 0x2A) {
                coord = Target->unknown_slot22();
                if (Target->Kind_Of() == 6) {
                    CoordStruct const &offset = ((UnknownBulletTargetBuilding *)Target)->Type->TargetCoordOffset;
                    if (offset.X != 0 || offset.Y != 0 || offset.Z != 0) {
                        coord = ((ObjectClass *)Target)->unknown_slot40();
                    }
                }
            }
        }
    }
    if (!Type->Airburst) {
        CoordStruct origin = coord;
        for (int index = 0; index < Type->Cluster; index++) {
            unknown_func_462110(coord);
            if (!unknown_7d) {
                return;
            }
            int distance = unknown_id_source_a3d290->Random()(0x100, 0x200);
            coord = Coord_Scatter(origin, distance, false);
        }
    } else {
        unknown_func_462110(coord);
    }
}
