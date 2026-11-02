// bool RocketLocomotionClass::Process() (0x0063DE90)
// The rocket state machine (+0x3C): 1 pause, 2 tilt from PitchInitial to
// PitchFinal over TiltFrames then launch (take-off anim and AuxSound1),
// 3 accelerate and climb to Altitude, 4 cruise (lazy-curve pitch blend or
// level flight until the dive point), 5 dive toward the destination; then
// trail anim, move along facing and pitch, and detonate on zero strength.
// False when the rocket detonated at the target (0x0063DCF0). Needs
// RA2_COORD_LENGTH (CoordStruct::Length), defined at the top of the unit.
#include "shared/rocket_locomotion.hpp"
#include "shared/fast_math.hpp"
#include "shared/point.hpp"

static inline int Square(int x) { return x * x; }

// double RocketLocomotionClass::unknown_63de10() (0x0063DE10): the pitch from
// the rocket to its destination, the arctangent of the height over the ground
// distance (straight down with no ground distance). The original emits it out
// of line with no callers; its standalone copy is not reproduced yet (88.89:
// the two squares take the opposite registers), so it is defined inline here
// and 0x0063DE10 stays unaccepted. Its two inlined copies below are exact.
inline double RocketLocomotionClass::unknown_63de10()
{
    CoordStruct coord = Object_Coord(LinkedTo);
    CoordStruct delta = unknown_18 - coord;
    float distance = Fast_Sqrt((double)(Square(delta.X) + Square(delta.Y)));
    if (distance > 0.0) {
        return Fast_Atan((double)(delta.Z / distance));
    }
    return -1.5707963267948966;
}

#include "shared/aircraft.hpp"
#include "shared/rules.hpp"
#include "shared/anim.hpp"
#include "shared/anim_type.hpp"
#include "shared/sound_play.hpp"
#include "shared/foot.hpp"
#include "shared/techno_type.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/point.hpp"
// The rocket's take-off and trail anim names (char const * variables).
extern char const *unknown_rocket_takeoff_anim_7ee804;  // 0x007EE804
extern char const *unknown_rocket_trail_anim_7ee808;    // 0x007EE808
// @ref ?unknown_rocket_takeoff_anim_7ee804@@3PBDB=007ee804
// @ref ?unknown_rocket_trail_anim_7ee808@@3PBDB=007ee808
// @ref ?Length@CoordStruct@@QBEHXZ=0041b780
// @ref ??0CoordStruct@@QAE@HHH@Z=0041b630

// Each LinkedTo->Center_Coord() below goes through a file-static helper:
// temporaries in inlined helpers share stack slots, temporaries in different
// cases of one switch do not (docs/VC6_MATCHING_NOTES.md).

// Westwood's Direction (TibSun inline.h): the facing from coord1 to coord2.
static inline UnknownFacingDir Direction_To(CoordStruct const &coord1, CoordStruct const &coord2)
{
    int x1 = coord1.X;
    int x2 = coord2.X;
    return UnknownFacingDir((unsigned short)(int)((Fast_Atan2((double)coord1.Y - (double)coord2.Y, (double)x2 - (double)x1) - 1.5707963267948966) * -10430.060040584269));
}

// Ground (x/y) distance from `to` to `from`. The take-off reading (case 3)
// sums y*y + x*x, the lazy-curve reading x*x + y*y (Ground_Distance2): the
// original's two inlined copies load the components in opposite orders.
static inline int Ground_Distance(TPoint2D<int> const &to, CoordStruct const &from)
{
    TPoint2D<int> delta = TPoint2D<int>(from.X, from.Y) - to;
    return (int)Fast_Sqrt((double)delta.Y * (double)delta.Y + (double)delta.X * (double)delta.X);
}

static inline int Ground_Distance(CoordStruct const &to, ObjectClass *object)
{
    return Ground_Distance(TPoint2D<int>(to.X, to.Y), object->Center_Coord());
}

static inline int Ground_Distance2(TPoint2D<int> const &to, CoordStruct const &from)
{
    TPoint2D<int> delta = TPoint2D<int>(from.X, from.Y) - to;
    return (int)Fast_Sqrt((double)delta.X * (double)delta.X + (double)delta.Y * (double)delta.Y);
}

static inline int Ground_Distance2(CoordStruct const &to, ObjectClass *object)
{
    return Ground_Distance2(TPoint2D<int>(to.X, to.Y), object->Center_Coord());
}

static inline UnknownFacingDir Direction_To(ObjectClass *object, CoordStruct const &to)
{
    return Direction_To(object->Center_Coord(), to);
}

static inline int Distance(CoordStruct const &coord1, CoordStruct const &coord2)
{
    CoordStruct delta = coord1 - coord2;
    return delta.Length();
}

static inline int Distance_To(ObjectClass *object, CoordStruct const &to)
{
    return Distance(object->Center_Coord(), to);
}
bool __stdcall RocketLocomotionClass::Process()
{
    RocketStruct const *rocket;
    if (((AircraftClass *)LinkedTo)->Type == Rules->V3Rocket.Type) {
        rocket = &Rules->V3Rocket;
    } else {
        rocket = &Rules->DMisl;
    }
    bool exploded = false;
    switch (unknown_40) {
    case 1:
        unknown_48 = 0;
        if (unknown_24.Progress() == 1.0) {
            unknown_40 = 2;
            unknown_24 = UnknownSlopeTimer(rocket->TiltFrames);
        }
        break;
    case 2:
        unknown_48 = 0;
        if (unknown_24.Progress() == 1.0) {
            unknown_50 = rocket->PitchFinal * 1.5707963267948966;
            unknown_40 = 3;
            if (LinkedTo->unknown_slot178() == unknown_geometry_k) {
                unknown_tracker_839ea0.Unknown_004131E0(LinkedTo);
            }
            new AnimClass(AnimTypes[AnimTypeClass::From_Name(unknown_rocket_takeoff_anim_7ee804)], Object_Coord(LinkedTo), 2, 1, 0x600, -10);
            Voc_Play_At(LinkedTo->unknown_slot32()->AuxSound1, Object_Coord(LinkedTo), 0);
        } else {
            float initial = rocket->PitchInitial * 1.5707963267948966;
            float final = rocket->PitchFinal * 1.5707963267948966;
            unknown_50 = initial + (final - initial) * unknown_24.Progress();
        }
        break;
    case 3:
        unknown_48 += rocket->Acceleration;
        if (unknown_48 > LinkedTo->unknown_slot32()->Speed) {
            unknown_48 = LinkedTo->unknown_slot32()->Speed;
        }
        if (LinkedTo->unknown_slot108() >= rocket->Altitude) {
            unknown_40 = 4;
            unknown_54 = Ground_Distance(unknown_18, LinkedTo);
        }
        break;
    case 4:
        unknown_48 += rocket->Acceleration;
        if (unknown_48 > LinkedTo->unknown_slot32()->Speed) {
            unknown_48 = LinkedTo->unknown_slot32()->Speed;
        }
        if (rocket->LazyCurve && unknown_54 != 0) {
            if (unknown_63dcf0(rocket)) {
                exploded = true;
            break;
            }
            int distance = Ground_Distance2(unknown_18, LinkedTo);
            double ratio = (double)distance / unknown_54;
            double rest = 1.0 - ratio;
            unknown_50 = unknown_63de10() * rest + rocket->PitchFinal * ratio * 1.5707963267948966;
        } else {
            if (unknown_50 > 0.0f) {
                unknown_50 -= rocket->TurnRate;
                if (unknown_50 < 0.0f) {
                    unknown_50 = 0;
                }
            }
            CoordStruct dest = unknown_18;
            CoordStruct coord = Object_Coord(LinkedTo);
            int height = coord.Z - dest.Z;
            dest.Z = Object_Coord(LinkedTo).Z;
            if (Distance_To(LinkedTo, dest) <= height) {
                unknown_40 = 5;
            }
        }
        LinkedTo->unknown_2e0.Set_Desired(Direction_To(LinkedTo, unknown_18));
        break;
    case 5:
        exploded = unknown_63dcf0(rocket);
        if (!exploded) {
            double diff = unknown_63de10() - unknown_50;
            float step = diff;
            if (step < 0.0) {
                step = -step;
            }
            if (step > rocket->TurnRate) {
                if (diff < 0.0) {
                    unknown_50 -= rocket->TurnRate;
                } else {
                    float rate = rocket->TurnRate;
                    unknown_50 += rate;
                }
            } else {
                unknown_50 += diff;
            }
        }
        break;
    }
    if (exploded) {
        return false;
    }
    if (Is_Moving_Now() && unknown_34 == 0) {
        new AnimClass(AnimTypes[AnimTypeClass::From_Name(unknown_rocket_trail_anim_7ee808)], Object_Coord(LinkedTo), 0, 1, 0x600, 0);
        unknown_34 = 3;
    }
    if (unknown_48 > 0.0) {
        CoordStruct coord = unknown_63dbe0((int)unknown_48);
        LinkedTo->unknown_slot103(coord);
        Cell cell = LinkedTo->unknown_slot104();
        if (cell != LinkedTo->unknown_458 && LinkedTo->unknown_7d) {
            unknown_tracker_839ea0.Unknown_00413600(LinkedTo, LinkedTo->unknown_458, cell);
        }
        if (LinkedTo->Strength <= 0) {
            unknown_63e7d0();
        }
    }
    return Is_Moving();
}
