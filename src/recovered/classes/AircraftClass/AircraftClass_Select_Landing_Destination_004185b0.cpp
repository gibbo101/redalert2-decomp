// AircraftClass::Select_Landing_Destination 0x004185B0 (Westwood's New_LZ): keeps a usable landing zone, otherwise
// scans rings of cells around it (eight directions from a random start) for a free landing cell.
// RulesClass +0x10E0 (the scan radius in leptons) is a hypothesis.
#include "shared/aircraft.hpp"
#include "shared/team.hpp"
#include "shared/map_view.hpp"
#include "shared/id_source.hpp"
// @ref ?Select_Landing_Destination_004185b0@AircraftClass@@QAEPAVAbstractClass@@PAV2@@Z=004185b0
// @ref ?Unknown_006BA990@TeamClass@@QAE_NXZ=006ba990
// @ref ?unknown_sin_4ba480@@YANN@Z=004ba480
// @ref ?unknown_cos_4ba4d0@@YANN@Z=004ba4d0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
double __cdecl unknown_sin_4ba480(double angle);
double __cdecl unknown_cos_4ba4d0(double angle);
// The direction in radians (Westwood's DirType::As_Radian).
inline double UnknownFacingDir::As_Radian() const
{
    return ((int)(short)Raw - 16383) * -9.587672516830327e-05;
}

// The cell a distance away in a direction (Westwood's Move_Cell).
static inline Cell Move_Cell(Cell const &start, UnknownFacingDir const &dir, short distance)
{
    double radians = dir.As_Radian();
    return Cell(start.X + unknown_cos_4ba4d0(radians) * distance, start.Y - unknown_sin_4ba480(radians) * distance);
}

AbstractClass *AircraftClass::Select_Landing_Destination_004185b0(AbstractClass *desired)
{
    if (desired) {
        if (Team && Team->Unknown_006BA990()) return desired;
        if (unknown_slot309(desired)) {
            Cell cell = Coord_Cell(desired->unknown_slot19(0));
            if (Is_Landing_Cell_Available_00419250(cell, false)) return desired;
        }
        CoordStruct coord = desired->Center_Coord();
        if (!unknown_a40774) {
            for (int radius = 0; radius < Rules->unknown_10e0 / 256; radius++) {
                int phase = unknown_id_source_a3d290->Random()(0, 7);
                Cell previous(0, 0);
                for (int direction = 0; direction < 8; direction++) {
                    Cell cell = Move_Cell(Coord_Cell(coord), UnknownFacingDir((unsigned short)(Facing_Dir(direction + phase).Raw & ~0x1fff)), radius);
                    if (Map.Unknown_0055A660(cell, true)) {
                        CellClass *candidate = &Map[cell];
                        if (cell != previous && unknown_slot309(candidate) &&
                            Is_Landing_Cell_Available_00419250(cell, false)) {
                            return candidate;
                        }
                        previous = cell;
                    }
                }
            }
        }
    }
    return desired;
}
