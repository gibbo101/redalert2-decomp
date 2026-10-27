// Bullet launch, typed member declarations authorized by owner0200Z.
// Bullet launch004616B0: independently bounded1343+1, twoRET8 sites.
#include "shared/bullet.hpp"
#include "shared/bullet_type.hpp"
#include "shared/weapon_type.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_static_rect.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/building.hpp"
#include "shared/rules.hpp"
#include "shared/random.hpp"
#include "shared/fast_math.hpp"
#include "shared/vector3.hpp"
CellClass *__fastcall Trace_Projectile_Line_004bb890(CoordStruct const &origin,
    CoordStruct const &destination, BulletTypeClass const *projectile, HouseClass const *house);
// @ref ?Trace_Projectile_Line_004bb890@@=004bb890
inline void Set_Projectile_Speed(BulletVelocity &velocity,double speed)
{
    if (velocity.X == 0.0 && velocity.Y == 0.0 && velocity.Z == 0.0) velocity.X = 100.0;
    double factor=speed/Fast_Sqrt(velocity.X*velocity.X+velocity.Y*velocity.Y+velocity.Z*velocity.Z);
    velocity.X*=factor; velocity.Y*=factor; velocity.Z*=factor;
}
inline float Projectile_Launch_Distance(CoordStruct const &source,CoordStruct const &target)
{
    Vector3 v((float)(source.X-target.X),(float)(target.Y-source.Y),(float)(source.Z-target.Z));
    float distance=Fast_Sqrt((double)v.X*v.X+(double)v.Y*v.Y+(double)v.Z*v.Z);
    return distance;
}
bool BulletClass::unknown_slot118(CoordStruct const &source, BulletVelocity const &velocity)
{
    if (ObjectClass::unknown_slot53(&source, 0)) {
        Velocity = velocity;
        SourceCoords = source;
        LastMapCoords = Coord_Cell(SourceCoords);
        Map.Remove(this);
        CoordStruct target = Target->unknown_slot22();
        TargetCoords = target;
        if (Type->FlakScatter && Type->Inviso) {
            float distance=Projectile_Launch_Distance(source,target);
            int maximum=Rules->unknown_139c*2;
            int scatter=unknown_id_source_a3d290->Random()(0,maximum);
            int product = (int)((unsigned int)scatter * (unsigned int)(int)distance); // original32-bit IMUL before signed IDIV
            int radius = product / WeaponType->unknown_b4;
            int random_direction = unknown_id_source_a3d290->Random()(0, 0x7ffffffe);
            // Full original conversion payloads verified in R1415 launch-data-proof.json.
            double random_angle = random_direction * 4.656612877414201e-10;
            random_angle *= 6.283185307179586;
            short raw_direction = (short)(int)((random_angle - 1.5707963267948966) * -10430.060040584269);
            int z=target.Z;
            double angle = ((int)raw_direction - 0x3fff) * -9.587672516830327e-05;
            int y = (int)((double)target.Y - Fast_Sin(angle) * (double)radius);
            int x = (int)(Fast_Cos(angle) * (double)radius + target.X);
            target = CoordStruct(x, y, z);
        }
        if (Type->Inviso) {
            HouseClass *house = Owner != 0 ? Owner->House : 0;
            CoordStruct collision = Map.Unknown_00569FB0(source, target, house);
            if (collision != unknown_geometry_l) {
                collision.Z = Map.Unknown_0055A280(collision);
                unknown_slot103(collision);
                BuildingClass *building = static_cast<BuildingClass *>(Map[collision].unknown_4717b0());
                building->Unknown_00450CB0(this, false);
                unknown_slot60();
            } else {
                CellClass *blocking = Trace_Projectile_Line_004bb890(source, target, Type, house);
                if (blocking != 0) unknown_slot103(blocking->Center_Coord());
                else unknown_slot103(target);
                // Original calls again even after the blocking-cell branch.
                unknown_slot103(target);
                Speed = 0;
                Set_Projectile_Speed(Velocity,0.0);
            }
        }
        int arm = Target != 0 && Target->Kind_Of() == 2 ? 0 : Type->Arm;
        Data.Initialize_004cee20(CoordStruct(Coord), target, arm, 0x7fffffff);
        if (Type->ROT > 0) {
            Set_Projectile_Speed(Velocity,1.0);
        }
        if (unknown_7d) Map.Submit(this);
        return true;
    }
    return false;
}

// @ref ?Unknown_00569FB0@MapClass@@=00569fb0
// @ref ?Unknown_00450CB0@BuildingClass@@=00450cb0
// @ref ?Initialize_004cee20@UnknownBulletData@@=004cee20

// @ref __real@8@4001c90fdaa22168c000=0079c9b8
// @ref __real@8@bff1c9116cc4faf2b800=0079b620
