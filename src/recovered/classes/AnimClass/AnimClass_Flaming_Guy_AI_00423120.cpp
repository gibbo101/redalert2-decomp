// void AnimClass::Flaming_Guy_AI() (0x00423120)
// Per-frame logic of a burning infantry animation (TibSun anim.cpp
// Flaming_Guy_AI): runs toward the next water cell (unknown_f0, TibSun
// FlamingGuyCoords; retries in unknown_fc), keeps the running frames pointed
// the way it goes, falls off a bridge edge (unknown_7a, IsFalling), and ends in
// the death sequence (unknown_17a, IsFlamingGuyEnd).
#include "shared/anim.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/facing.hpp"
#include "shared/fast_math.hpp"
#include "shared/shape_file.hpp"
#include "shared/adjacent_cell.hpp"
#include "shared/building_light.hpp"
#include "shared/unknown_vector3.hpp"
// @ref ??0UnknownVector3@@QAE@HHH@Z=0041b630
// @ref ?Length@UnknownVector3@@QBEHXZ=0041b780
extern double const unknown_facing_scale_79b628;
extern double const unknown_facing_origin_79b630;
// @ref ?unknown_facing_scale_79b628@@3NB=0079b628
// @ref ?unknown_facing_origin_79b630@@3NB=0079b630
// @ref ?unknown_facing_radians_79b620@@3NB=0079b620
// @ref ?Direction@UnknownFacingDir@@QAEAAU1@ABUCoordStruct@@0@Z=00423ef0
// @ref ?Fast_Atan2@@YAMNN@Z=004ba600
// @ref ?unknown_sin_4ba480@@YANN@Z=004ba480
// @ref ?unknown_cos_4ba4d0@@YANN@Z=004ba4d0
// @ref ?Frame@@3HA=00a40d2c
// @ref _unknown_geometry_l=0084c6d0
// @ref _unknown_geometry_g=0084c708
// @ref _unknown_geometry_j=0084c6f8
// @ref __ftol=0077f110
// @ref __real@8@40039000000000000000=0079c288
// @ref ?unknown_func_4237b0@AnimClass@@QAE?AUCoordStruct@@XZ=004237b0

// The point DISTANCE leptons from START toward DIR (TibSun inline.h Move_Coord; Z kept).
static inline CoordStruct Move_Coord(CoordStruct const &start, UnknownFacingDir const &dir, int distance)
{
    double radians = ((short)dir.Raw - 0x3fff) * unknown_facing_radians_79b620;
    return CoordStruct((int)(start.X + unknown_cos_4ba4d0(radians) * distance), (int)(start.Y - unknown_sin_4ba480(radians) * distance), start.Z);
}

// The direction from one coordinate to another (TibSun inline.h Direction).
static inline UnknownFacingDir Direction(CoordStruct const &coord1, CoordStruct const &coord2)
{
    int x1 = coord1.X;
    int x2 = coord2.X;
    return UnknownFacingDir((unsigned short)(int)((Fast_Atan2((double)coord1.Y - (double)coord2.Y, (double)x2 - (double)x1)
        - unknown_facing_origin_79b630) * unknown_facing_scale_79b628));
}

// The offset between two coordinates (TibSun Coord::operator-).
static inline UnknownVector3 Flaming_Offset(CoordStruct const &from, CoordStruct const &to)
{
    return UnknownVector3(from.X - to.X, from.Y - to.Y, from.Z - to.Z);
}

// The cell next to CELL toward an 8-way facing, the cell as the left operand.
static inline Cell Flaming_Adjacent_Cell(Cell const &cell, int facing)
{
    return cell + AdjacentCell[facing & 7];
}

void AnimClass::Flaming_Guy_AI()
{
    if (!unknown_17a) {
        Set_Rate(0);
    }

    if (unknown_f0 != unknown_geometry_l && !unknown_17a) {
        CoordStruct coord = Coord;
        coord.Z = 0;
        CoordStruct target = unknown_f0;
        target.Z = 0;
        if (Flaming_Offset(coord, target).Length() <= 18) {
            if (!unknown_7a) {
                CoordStruct nextcoord = unknown_func_4237b0();
                bool sink = (Map[unknown_f0].unknown_ec == 2 || Map[unknown_f0].unknown_ec == 6) && unknown_slot108() <= unknown_geometry_g;
                if (nextcoord != unknown_geometry_l && unknown_fc < 7 && !sink) {
                    unknown_fc++;
                    int z = Position_Coord_004f3f40().Z;
                    CoordStruct oldcoord = unknown_f0;
                    if (z <= Map.Unknown_0055A280(oldcoord) + 2 * unknown_geometry_g) {
                        oldcoord.Z = Map.Unknown_0055A280(oldcoord);
                    } else {
                        oldcoord.Z = Map.Unknown_0055A280(oldcoord) + unknown_geometry_j;
                    }
                    unknown_slot103(oldcoord);
                    unknown_f0 = nextcoord;
                } else {
                    unknown_f0 = unknown_geometry_l;
                    unknown_17a = true;
                    Set_Rate(1);
                    Stage = Class->RunningFrames * 8 + 1;
                    return;
                }
            }
        } else {
            int z = Position_Coord_004f3f40().Z;
            UnknownFacingDir direction = UnknownFacingDir().Direction(Center_Coord(), unknown_f0);
            CoordStruct newcoord = Move_Coord(Position_Coord_004f3f40(), direction, 18);
            if (z <= Map.Unknown_0055A280(newcoord) + 2 * unknown_geometry_g) {
                newcoord.Z = Map.Unknown_0055A280(newcoord);
            } else {
                newcoord.Z = Map.Unknown_0055A280(newcoord) + unknown_geometry_j;
            }
            unknown_slot103(newcoord);
        }

        if (!unknown_7a) {
            Cell position = Position_Coord_004f3f40();
            if (Position_Coord_004f3f40().Z >= Map.Unknown_0055A280(Position_Coord_004f3f40()) + unknown_geometry_j) {
                if (!(Map[Position_Coord_004f3f40()].unknown_140 & 0x100) && !(Map[Flaming_Adjacent_Cell(position, 6)].unknown_140 & 0x100) && !(Map[Flaming_Adjacent_Cell(position, 0)].unknown_140 & 0x100)) {
                    unknown_7a = true;
                }
            }
        }
    } else {
        if (!unknown_7a) {
            if (!unknown_17a) {
                CoordStruct nextcoord = unknown_func_4237b0();
                if (nextcoord != unknown_geometry_l) {
                    unknown_f0 = nextcoord;
                } else {
                    unknown_f0 = unknown_geometry_l;
                    unknown_17a = true;
                    Set_Rate(1);
                    Stage = Class->RunningFrames * 8 + 1;
                }
            }
        }
    }

    if (!unknown_17a) {
        int stage = 0;
        if (unknown_f0 != unknown_geometry_l) {
            stage = Class->RunningFrames * ((-1 - Dir_To_8(Direction(Center_Coord(), unknown_f0))) & 7);
        }
        Stage = stage + Frame / 3 % Class->RunningFrames;
        return;
    } else {
        int stage = ((ShapeFileStruct const *)unknown_slot26())->FrameCount / 2 - 1;
        if (Stage >= stage) {
            unknown_slot60();
        }
    }
}
