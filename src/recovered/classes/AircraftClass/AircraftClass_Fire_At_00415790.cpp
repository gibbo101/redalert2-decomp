// AircraftClass::Fire_At (slot 221, 0x00415790): fires the techno weapon, then aims a
// projectile's velocity (level flight for ROT 0, straight at the target for ROT 1) and
// reveals the area around a player aircraft that fires from or into the shroud.
#include "shared/aircraft.hpp"
#include "shared/bullet.hpp"
#include "shared/bullet_type.hpp"
#include "shared/weapon_type.hpp"
#include "shared/unknown_vector3.hpp"
#include "shared/aircraft_vector_xy.hpp"
#include "shared/house.hpp"
#include "shared/map_view.hpp"
#include "shared/rules.hpp"
#include "shared/fast_math.hpp"
#include "shared/facing.hpp"

// @ref ?Get_Pitch@BulletVelocity@@QBE?AUUnknownFacingDir@@XZ=0041b6e0
double __fastcall Velocity_Length3_0041B7C0(BulletVelocity const *velocity);
void __fastcall Ensure_Velocity3_0041B7F0(BulletVelocity *velocity);
double __fastcall Velocity_LengthXY_0041B830(BulletVelocity const *velocity);
void __fastcall Ensure_VelocityXY_0041B860(BulletVelocity *velocity);
double __fastcall Aircraft_XY_Length_0041B750(AircraftVectorXY const *vector);

inline void UnknownFacingDir::From_Radian(double angle)
{
    Raw = (unsigned short)(short)((angle - 1.5707963267948966) * -10430.060040584269);
}
// Westwood's TVelocity3D::Set_Speed.
static inline void Set_Speed(BulletVelocity &velocity, double speed)
{
    Ensure_Velocity3_0041B7F0(&velocity);
    double ratio = speed / Velocity_Length3_0041B7C0(&velocity);
    velocity.X *= ratio;
    velocity.Y *= ratio;
    velocity.Z *= ratio;
}

// Westwood's TVelocity3D::Set_Pitch.
static inline void Set_Pitch(BulletVelocity &velocity, UnknownFacingDir const &pitch)
{
    double current_pitch = velocity.Get_Pitch().As_Radian();
    double speed = Velocity_Length3_0041B7C0(&velocity);
    if (current_pitch != 0) {
        velocity.X /= Fast_Cos(current_pitch);
        velocity.Y /= Fast_Cos(current_pitch);
    }
    velocity.X *= Fast_Cos(pitch.As_Radian());
    velocity.Y *= Fast_Cos(pitch.As_Radian());
    velocity.Z = speed * Fast_Sin(pitch.As_Radian());
}

// Westwood's TVelocity2D::Set_Yaw.
static inline void Set_Yaw(BulletVelocity &velocity, UnknownFacingDir const &yaw)
{
    Ensure_VelocityXY_0041B860(&velocity);
    double horizontal_speed = Velocity_LengthXY_0041B830(&velocity);
    double x = horizontal_speed * Fast_Cos(yaw.As_Radian());
    velocity.X = x;
    velocity.Y = -horizontal_speed * Fast_Sin(yaw.As_Radian());
}

// Westwood's TVelocity2D::Get_Yaw.
static inline UnknownFacingDir Get_Yaw(BulletVelocity const &velocity)
{
    UnknownFacingDir dir;
    dir.From_Radian(Fast_Atan2(-velocity.Y, velocity.X));
    return dir;
}

// Westwood's TVelocity3D::Get_Pitch, expanded here (the horizontal speed stays out of line).
static inline UnknownFacingDir Get_Pitch(BulletVelocity const &velocity)
{
    UnknownFacingDir dir;
    dir.From_Radian(Fast_Atan2(velocity.Z, Aircraft_XY_Length_0041B750((AircraftVectorXY const *)&velocity)));
    return dir;
}

// The difference between two coordinates.
static inline UnknownVector3 Coord_Difference(CoordStruct const &to, CoordStruct const &from)
{
    return UnknownVector3(to.X - from.X, to.Y - from.Y, to.Z - from.Z);
}

// A coordinate moved by an offset.
static inline UnknownVector3 Offset(CoordStruct coord, UnknownVector3 const &offset)
{
    return UnknownVector3(offset.X + coord.X, offset.Y + coord.Y, offset.Z + coord.Z);
}

// A vector as a coordinate.
static inline CoordStruct As_Coord(UnknownVector3 const &vector)
{
    return *(CoordStruct const *)&vector;
}

// Westwood's Coord: a point with an inline (x, y, z = 0) constructor over the out-of-line base one.
struct OffsetCoord : public UnknownVector3 {
    OffsetCoord(int x, int y, int z = 0) : UnknownVector3(x, y, z) {}
};

BulletClass *AircraftClass::unknown_slot221(AbstractClass *target, int arg2)
{
    if (Cargo.Object) {
        unknown_415510();
        return 0;
    }

    BulletClass *bullet = TechnoClass::unknown_slot221(target, arg2);
    if (bullet) {
        if (bullet->Type->ROT == 0) {
            Set_Speed(bullet->Velocity, Locomotor.Checked()->Apparent_Speed());
            Set_Pitch(bullet->Velocity, UnknownFacingDir(0x4000));
            Set_Yaw(bullet->Velocity, unknown_2f8.Current());
        }

        if (bullet->Type->ROT == 1) {
            UnknownVector3 diff = Coord_Difference(target->Center_Coord(), Center_Coord());
            BulletVelocity dir = BulletVelocity(diff.X, diff.Y, diff.Z);
            Set_Yaw(bullet->Velocity, Get_Yaw(dir));
            Set_Pitch(bullet->Velocity, Get_Pitch(dir));
            Set_Speed(bullet->Velocity, unknown_slot231(0)->WeaponType->unknown_a8);
        }

        if (House->Unknown_004F52B0()) {
            if (Map.Unknown_00568140(Position_Coord_004f3f40()) ||
                Map.Unknown_00568140(As_Coord(Offset(Position_Coord_004f3f40(), OffsetCoord(512, 512)))) ||
                Map.Unknown_00568140(As_Coord(Offset(Position_Coord_004f3f40(), OffsetCoord(-512, -512)))) ||
                Map.Unknown_00568140(As_Coord(Offset(Position_Coord_004f3f40(), OffsetCoord(512, -512)))) ||
                Map.Unknown_00568140(As_Coord(Offset(Position_Coord_004f3f40(), OffsetCoord(512, -512)))) ||
                Map.Unknown_00568140(target->Center_Coord())) {
                Map.Sight_From(Position_Coord_004f3f40(), Rules->AttackingAircraftSightRange, House, 0, 0, 0, 1, 0);
                Map.Sight_From(Position_Coord_004f3f40(), Rules->AttackingAircraftSightRange, House, 0, 0, 0, 1, 1);
            }
        }
    }
    if (unknown_5b2) {
        unknown_slot60();
    }
    return bullet;
}
// @ref ?unknown_415510@AircraftClass@@QAEHXZ=00415510
// @ref ?unknown_slot221@TechnoClass@@UAEPAVBulletClass@@PAVAbstractClass@@H@Z=006ca890
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?Ensure_Velocity3_0041B7F0@@YIXPAUBulletVelocity@@@Z=0041b7f0
// @ref ?Velocity_Length3_0041B7C0@@YINPBUBulletVelocity@@@Z=0041b7c0
// @ref __real@8@bff1c9116cc4faf2b800=0079b620
// @ref __real@8@00000000000000000000=0079b610
// @ref ?Fast_Cos@@YAMN@Z=004ba4d0
// @ref ?Fast_Sin@@YAMN@Z=004ba480
// @ref ?Current@FacingClass@@QBE?AUUnknownFacingDir@@XZ=004b8be0
// @ref ?Ensure_VelocityXY_0041B860@@YIXPAUBulletVelocity@@@Z=0041b860
// @ref ?Velocity_LengthXY_0041B830@@YINPBUBulletVelocity@@@Z=0041b830
// @ref ??0UnknownVector3@@QAE@HHH@Z=0041b630
// @ref ?Fast_Atan2@@YAMNN@Z=004ba600
// @ref __real@8@3fffc90fdaa22168c000=0079b630
// @ref __real@8@c00ca2f83d7b47677800=0079b628
// @ref __ftol=0077f110
// @ref ?Aircraft_XY_Length_0041B750@@YINPBUAircraftVectorXY@@@Z=0041b750
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_00568140@MapClass@@QAE_NABUCoordStruct@@@Z=00568140
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Sight_From@MapClass@@QAEXABUCoordStruct@@HPAVHouseClass@@_N2222@Z=0054a110
