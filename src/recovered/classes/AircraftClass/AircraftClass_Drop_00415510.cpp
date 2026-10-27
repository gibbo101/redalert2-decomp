// Aircraft drop helper00415510,original629+11;private current-header diagnostic.
// int-zero return spelling is a hypothesis from both original EAX-zero exits;
// callers ignore the return, so no original source-level return type is claimed.
#include "shared/aircraft.hpp"
#include "shared/map_view.hpp"
#include "shared/team.hpp"
// @ref _unknown_geometry_l=0083c498
// @ref ?unknown_angle_scale_79b620@@3NB=0079b620
// @ref ?unknown_sin_4ba480@@YANN@Z=004ba480
// @ref ?unknown_cos_4ba4d0@@YANN@Z=004ba4d0
// @ref __real@8@40068000000000000000=0079b618
extern double const unknown_angle_scale_79b620;
double __cdecl unknown_sin_4ba480(double angle);
double __cdecl unknown_cos_4ba4d0(double angle);

int AircraftClass::unknown_415510()
{
    // Cargo detach's FootClass result association remains a layout hypothesis.
    FootClass *passenger = static_cast<FootClass *>(Cargo.unknown_4689f0());
    if (passenger) {
        --unknown_254;
        CoordStruct landing = Center_Coord();
        UnknownFacingDir facing;
        if (unknown_254 & 1) {
            facing = UnknownFacingDir((unsigned short)(unknown_2e0.Current().Raw - 0x3fff));
        } else {
            facing = UnknownFacingDir((unsigned short)(unknown_2e0.Current().Raw + 0x3fff));
        }
        double angle = ((short)facing.Raw - 0x3fff) * unknown_angle_scale_79b620;
        int altitude = landing.Z;
        double center_y = landing.Y;
        int sample_y = (int)(center_y - unknown_sin_4ba480(angle) * 128.0);
        int sample_x = (int)(unknown_cos_4ba4d0(angle) * 128.0 + landing.X);
        landing = CoordStruct(sample_x, sample_y, altitude);
        CellClass *map_cell = &Map[landing];
        UnknownCellClass *cell = reinterpret_cast<UnknownCellClass *>(map_cell);
        if (passenger->unknown_slot101(map_cell, -1, 0, 0, 1) == 0) {
            CoordStruct spot = cell->Unknown_004764B0(landing, 0, false);
            if (spot != unknown_geometry_l) {
                // The original tests spot.Z, but retains the aircraft altitude.
                landing.X = spot.X;
                landing.Y = spot.Y;
                if (passenger->unknown_slot56(landing)) {
                    {
                    CoordStruct sound_position = Coord;
                    Unknown_00713E60(Rules->ChuteSound, sound_position, 0);
                    }
                    passenger->unknown_454 = Coord_Cell(Map[landing].Center_Coord());
                    if (Team) Team->Unknown_006B8FB0(passenger, -1, 0);
                    unknown_244 = CDTimerClass<FrameTimerClass>(0);
                    unknown_5bb = 5;
                    return 0;
                }
            }
        }
        Cargo.Unknown_00468960(passenger);
        passenger->unknown_slot69();
        ++unknown_254;
    }
    return 0;
}
