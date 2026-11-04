// unsigned char __stdcall HoverLocomotionClass::Process() (0x004FBFC0, ILocomotion 16)
// TibSun hover.cpp HoverLocomotionClass::Process, statement for statement,
// with RA2's radio-contact arrival test and wake/bridge rules.
#include "shared/hover_locomotion.hpp"
#include "shared/cell_class.hpp"
#include "shared/anim.hpp"
#include "shared/rules.hpp"
#include "shared/fast_math.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?Current@FacingClass@@QBE?AUUnknownFacingDir@@XZ=004b8be0
// @ref ?Set_Current@FacingClass@@QAE_NABUUnknownFacingDir@@@Z=004b8b10
// @ref ?Equal_XY_004bfb60@CoordStruct@@QBEHABU1@@Z=004bfb60
// @ref ?Fast_Atan2@@YAMNN@Z=004ba600
// @ref ?Fast_Sqrt@@YAMN@Z=004ba410
// @ref ?Fast_Sin@@YAMN@Z=004ba480
// @ref ?Fast_Cos@@YAMN@Z=004ba4d0
// @ref ?unknown_coord_a41080@@3UCoordStruct@@A=00a41080
// @ref ?unknown_facing_origin_79b630@@3NB=0079b630
// @ref ?unknown_facing_scale_79b628@@3NB=0079b628
// @ref ?unknown_move_angle_scale_79b620@@3NB=0079b620
// @ref ?While_Moving_004fcbc0@HoverLocomotionClass@@QAEH_N@Z=004fcbc0
// @ref ?Start_Of_Move_004fe0f0@HoverLocomotionClass@@QAEXH@Z=004fe0f0
// @ref ?Motion_AI_004fdaf0@HoverLocomotionClass@@QAEXXZ=004fdaf0
// @ref ?Gravity_AI_004fb9d0@HoverLocomotionClass@@QAEXXZ=004fb9d0
// @ref ??8Cell@@QBE_NABV0@@Z=004fef20
// @ref ?As_Cell@CoordStruct@@QBE?AVCell@@XZ=00413770
// @ref ?Contact@RadioClass@@QBEPAVTechnoClass@@H@Z=00636e10
// @ref ?unknown_func_5d4920@ObjectClass@@QAEXH@Z=005d4920
// @ref ??AMapClass@@QAEAAVCellClass@@ABUCoordStruct@@@Z=00548000
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280
// @ref ?unknown_47bb30@CellClass@@QAEXXZ=0047bb30
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Frame@@3HA=00a40d2c
// @ref ??0AnimClass@@QAE@PBVAnimTypeClass@@ABUCoordStruct@@HHHH@Z=00420110
// @ref _unknown_geometry_g=00a410b8
// @ref _unknown_geometry_j=00a410a8
// @ref _unknown_geometry_k=00a41060
// @ref __ftol=0077f110
extern double const unknown_facing_origin_79b630;
extern double const unknown_facing_scale_79b628;
extern double const unknown_move_angle_scale_79b620;

inline UnknownFacingDir Hover_Direction_004fbfc0(CoordStruct const &from, CoordStruct const &to)
{
    UnknownFacingDir direction;
    if (from.Equal_XY_004bfb60(to)) direction.Raw = 0;
    direction = UnknownFacingDir((unsigned short)(int)((Fast_Atan2(double(from.Y) - to.Y, double(to.X) - from.X) - unknown_facing_origin_79b630) * unknown_facing_scale_79b628));
    return direction;
}

// TibSun's Point2D(Coord) conversion.
inline TPoint2D<int> Hover_Point_004fbfc0(CoordStruct const &coord)
{
    return TPoint2D<int>(coord.X, coord.Y);
}

// TibSun Point2D::Distance_To.
inline int Hover_Distance_004fbfc0(CoordStruct const &from, CoordStruct const &to)
{
    TPoint2D<int> difference = TPoint2D<int>(from.X, from.Y) - TPoint2D<int>(to.X, to.Y);
    return (int)Fast_Sqrt((double)difference.X * difference.X + (double)difference.Y * difference.Y);
}

inline TPoint2D<int> Hover_Move_Point_004fbfc0(TPoint2D<int> const &start, UnknownFacingDir const &facing, int distance)
{
    double angle = ((short)facing.Raw - 0x3fff) * unknown_move_angle_scale_79b620;
    return TPoint2D<int>((int)(double(start.X) + Fast_Cos(angle) * double(distance)),
        (int)(double(start.Y) - Fast_Sin(angle) * double(distance)));
}
inline UnknownFacingDir operator+(UnknownFacingDir const &left, int right)
{
    return UnknownFacingDir((unsigned short)(left.Raw + right));
}
inline int Dir256_004fbfc0(int facing) { return facing << 8; }
inline unsigned Hover_Under_Bridge_004fbfc0(CellClass const *cell) { return cell->unknown_140 & 0x100; }
inline int Hover_Abs_004fbfc0(int value) { return abs(value); }
inline UnknownFacingDir operator-(UnknownFacingDir const &left, UnknownFacingDir const &right)
{
    return UnknownFacingDir((unsigned short)(left.Raw - right.Raw));
}
inline bool operator>=(UnknownFacingDir const &left, UnknownFacingDir const &right)
{
    return abs((short)left.Raw) >= abs((short)right.Raw);
}
inline bool Is_Complete_Turn(UnknownFacingDir const &current, UnknownFacingDir const &towards, UnknownFacingDir const &by)
{
    UnknownFacingDir diff(current - towards);
    if (by >= diff) {
        return true;
    }
    return false;
}
unsigned char __stdcall HoverLocomotionClass::Process()
{
    if (Is_Moving() && unknown_4fdfc0()) {
        Motion_AI_004fdaf0();
        if (!LinkedTo->unknown_7d) return false;

        int height = LinkedTo->unknown_slot110();
        int speed = (int)(LinkedTo->unknown_slot303() * unknown_50);
        UnknownFacingDir direction = Hover_Direction_004fbfc0(LinkedTo->Center_Coord(), unknown_24);

        if (speed == 0 && Is_Complete_Turn(unknown_30.Current(), direction, UnknownFacingDir((unsigned short)0))) {
            unknown_4fed20();
            speed = (int)(LinkedTo->unknown_slot303() * unknown_50);
        }

        if (speed >= Hover_Distance_004fbfc0(Object_Coord(LinkedTo), unknown_24)) {
            LinkedTo->unknown_5a0 = true;
            LinkedTo->unknown_5a1 = false;
            unknown_70 = false;

            Start_Of_Move_004fe0f0(0);

            if (LinkedTo->unknown_4d0 == -1 && unknown_18 == unknown_coord_a41080) {
                unknown_24 = unknown_coord_a41080;
            }

            TechnoClass *contact = LinkedTo->Contact(0);
            Cell cell = unknown_geometry_k;
            if (contact) cell = Coord_Cell(contact->unknown_slot19(LinkedTo));
            bool arrived = LinkedTo->unknown_slot104() == cell;

            if (unknown_18 != unknown_coord_a41080 || arrived) {
                int ok = While_Moving_004fcbc0(true);
                int const &result = ok;
                if (!LinkedTo->unknown_7d || LinkedTo->unknown_76 || LinkedTo->unknown_7a) return 7;
                if (result == 0 && unknown_24 == unknown_coord_a41080) {
                    LinkedTo->unknown_slot93(2);
                    if (!LinkedTo->unknown_7d || LinkedTo->unknown_76 || LinkedTo->unknown_7a) return false;
                }
                if (ok == 7) {
                    if (LinkedTo->unknown_574 >= 0) return false;
                    Stop();
                } else if (ok != 0) {
                    unknown_4fda80();
                    speed = 0;
                }
            }
        }

        if (speed > 0) {
            CoordStruct coord = Object_Coord(LinkedTo);

            if (LinkedTo->unknown_slot47() && unknown_24 != unknown_coord_a41080) {
                LinkedTo->unknown_slot59(Object_Coord(LinkedTo));
                LinkedTo->unknown_5a0 = false;
                LinkedTo->unknown_5a1 = false;
            }

            TPoint2D<int> moved = Hover_Move_Point_004fbfc0(Hover_Point_004fbfc0(coord), unknown_30.Current(), speed);
            coord.X = moved.X;
            coord.Y = moved.Y;
            if (coord.As_Cell() != Object_Coord(LinkedTo).As_Cell()) {
                LinkedTo->unknown_slot71(0);
                LinkedTo->unknown_slot103(coord);
                LinkedTo->unknown_func_5d4920(height);
                CellClass *cellptr = &Map[coord];
                if (!LinkedTo->unknown_79 && Hover_Under_Bridge_004fbfc0(cellptr) && LinkedTo->unknown_slot108() >= unknown_geometry_j) {
                    LinkedTo->unknown_79 = true;
                }
                if (LinkedTo->unknown_79 == true && !Hover_Under_Bridge_004fbfc0(cellptr)) {
                    LinkedTo->unknown_79 = false;
                }
                LinkedTo->unknown_slot71(1);
            } else {
                bool wasdown = LinkedTo->unknown_74;
                LinkedTo->unknown_74 = false;
                LinkedTo->unknown_slot103(coord);
                LinkedTo->unknown_func_5d4920(height);
                LinkedTo->unknown_74 = wasdown;
            }
        }
    }

    if (Is_Moving_Now() && (Frame % 10) == 0) {
        if (!LinkedTo->unknown_79 && static_cast<CellClass *>(LinkedTo->unknown_slot105())->Land_Type() == 2) {
            if (Rules->unknown_09c != 0) {
                new AnimClass(Rules->unknown_09c, Object_Coord(LinkedTo), 0, 1, 0x600, 0);
            }
        }
    }

    Gravity_AI_004fb9d0();

    if (unknown_68) {
        if (Is_Powered()) {
            UnknownFacingDir dir = LinkedTo->unknown_2e0.Current();
            LinkedTo->unknown_2e0.Set_Current(dir + Dir256_004fbfc0(unknown_6c));
            int delta = Hover_Abs_004fbfc0(unknown_6c);
            if (delta >= 1) {
                delta = 1;
            }
            if (unknown_6c < 0) {
                unknown_6c += delta;
            } else {
                unknown_6c -= delta;
            }
            if (unknown_6c == 0) {
                unknown_68 = false;
            }
        } else {
            unknown_68 = false;
        }
        if (!unknown_68) {
            Map[Object_Coord(LinkedTo)].unknown_47bb30();
            if (Map[Object_Coord(LinkedTo)].Land_Type() == 2) {
                if (Object_Coord(LinkedTo).Z < Map.Unknown_0055A280(Object_Coord(LinkedTo)) + unknown_geometry_g) {
                    LinkedTo->unknown_slot57();
                }
            }
        }
    }

    return Is_Moving();
}
