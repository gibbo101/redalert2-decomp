// AircraftClass Good_Fire_Location 0x00418F10 (name from TibSun aircraft.cpp; thiscall, ret 4): searches rings
// of cells around the target for a landing-capable firing spot, nearest to the target's NavCom (or to this
// aircraft), and returns the best or the second-best cell at random.
#include "shared/aircraft.hpp"
#include "shared/map_view.hpp"
#include "shared/id_source.hpp"
// @ref _unknown_geometry_k=0083c478
// @ref _unknown_geometry_l=0083c498
// @ref ?unknown_sin_4ba480@@YANN@Z=004ba480
// @ref ?unknown_cos_4ba4d0@@YANN@Z=004ba4d0
// @ref ?unknown_angle_scale_79b620@@3NB=0079b620
// @ref ?Is_Landing_Cell_Available_00419250@AircraftClass@@QAE_NABVCell@@_N@Z=00419250
extern double const unknown_angle_scale_79b620;
double __cdecl unknown_sin_4ba480(double angle);
double __cdecl unknown_cos_4ba4d0(double angle);

// Explicit modulo-2^32 coordinate subtraction, as executed by the original SUB.
static inline int Aircraft_Wrapped_Subtract_00418F10(int left, int right)
{
    return (int)((unsigned int)left - (unsigned int)right);
}

// The ground-plane point of a coordinate.
static inline Point2D As_Point(CoordStruct const &coord)
{
    return Point2D(coord.X, coord.Y);
}

// The length of a point taken as a vector (Westwood's TPoint2D::Length).
static inline int Point_Length(Point2D const &point)
{
    return (int)unknown_sqrt_4ba410((double)point.X * (double)point.X + (double)point.Y * (double)point.Y);
}

// The distance between two points (Westwood's TPoint2D::Distance_To).
static inline int Point_Distance(Point2D const &from, Point2D const &to)
{
    return Point_Length(from - to);
}

AbstractClass *AircraftClass::unknown_418f10(AbstractClass *desired)
{
    if (desired) {
        if (Is_Strafe()) return desired;

        int range = unknown_slot85(0);
        CoordStruct center = desired->Center_Coord();
        Cell best_cell = unknown_geometry_k;
        Cell previous_record_cell = unknown_geometry_k;
        int best_distance = -1;
        int previous_record_distance = -1;
        CoordStruct destination = unknown_geometry_l;
        if (desired->AbstractFlags.IsFoot) {
            AbstractClass *next = static_cast<FootClass *>(desired)->unknown_494;
            if (next) destination = next->Center_Coord();
        }

        int radius = Aircraft_Wrapped_Subtract_00418F10(range, 256);
        if (radius > 256) {
            double center_y = center.Y;
            double center_x = center.X;
            do {
                double ring_radius = radius;
                for (int direction = 0; direction < 255; direction += 16) {
                    double angle = ((short)((unsigned char)direction << 8) - 0x3fff)
                                   * unknown_angle_scale_79b620;
                    int sample_y = (int)(center_y - unknown_sin_4ba480(angle) * ring_radius);
                    int sample_x = (int)(unknown_cos_4ba4d0(angle) * ring_radius + center_x);
                    Cell sample = XY_Cell(sample_x / 256, sample_y / 256);
                    Cell cell = sample;
                    if (Map.Unknown_0055A660(cell, true) &&
                        (unknown_game_mode_a3d298 || unknown_32c ||
                         (reinterpret_cast<UnknownCellClass *>(&Map[cell])->unknown_12c & 0x10)) &&
                        Is_Landing_Cell_Available_00419250(cell, true)) {
                        int distance;
                        if (destination != unknown_geometry_l) {
                            distance = Point_Distance(Point2D(sample_x, sample_y), Point2D(destination.X, destination.Y));
                        } else {
                            distance = Point_Distance(As_Point(Center_Coord()), Point2D(sample_x, sample_y));
                        }
                        if (best_distance == -1 || distance < best_distance) {
                            previous_record_distance = best_distance;
                            previous_record_cell = best_cell;
                            best_distance = distance;
                            best_cell = cell;
                        }
                    }
                }
                if (best_distance != -1) break;
                radius -= 256;
            } while (radius > 256);
        }
        if (previous_record_distance == -1) previous_record_cell = best_cell;
        if (best_distance != -1) {
            if (unknown_id_source_a3d290->Random()(0, 99) < 50) return &Map[best_cell];
            return &Map[previous_record_cell];
        }
    }
    return 0;
}


// Aircraft landing-cell predicate00419250. Boolean return spelling is a hypothesis.
#include "shared/aircraft.hpp"
#include "shared/map_view.hpp"
// @ref ?Unknown_0055A660@MapClass@@QAE_NABVCell@@_N@Z=0055a660
// @ref ?unknown_471660@CellClass@@QBEPAVObjectClass@@ABUPoint2D@@_NPAV2@@Z=00471660
