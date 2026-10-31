// AircraftClass::unknown_4198b0 0x004198B0: where to land (Good_LZ): the cell next to the nearest
// dock building (distance quartered for the first dock type), else next to the nearest own techno,
// else the aircraft's own cell.
#include "shared/aircraft.hpp"
#include "shared/house.hpp"
#include "shared/map_view.hpp"
#include "shared/object_lists.hpp"
#include "shared/unknown_vector3.hpp"
#include "shared/unknown_geometry.hpp"
// @ref _unknown_geometry_k=0083c478

// The distance between two coordinates through UnknownVector3 (0x0041B630/0x0041B780, out of line).
static inline int Vector_Distance(CoordStruct const &here, CoordStruct const &there)
{
    UnknownVector3 delta = UnknownVector3(here.X - there.X, here.Y - there.Y, here.Z - there.Z);
    return delta.Length();
}

// The same distance computed inline from the coordinate difference.
static inline int Coord_Distance(CoordStruct const &here, CoordStruct const &there)
{
    CoordStruct delta(here.X - there.X, here.Y - there.Y, here.Z - there.Z);
    double y = delta.Y;
    double z = delta.Z;
    double x = delta.X;
    return (int)unknown_sqrt_4ba410(x * x + z * z + y * y);
}

AbstractClass *AircraftClass::unknown_4198b0()
{
    Cell best_cell = Cell(0, 0);
    int best_distance = -1;
    int index;

    if (Type->Dock.Count() > 0) {
        int count = House->Buildings.Count();
        for (index = 0; index < count; index++) {
            BuildingClass *building = House->Buildings[index];
            if (building && !building->unknown_76) {
                int distance = Vector_Distance(Center_Coord(), building->Center_Coord());
                if (building->Type == Type->Dock[0]) {
                    distance /= 4;
                }
                if (best_distance == -1 || distance < best_distance) {
                    Cell cell = building->unknown_slot104();
                    cell = Map.Unknown_005502E0(cell, 0, Map.Zone(cell, 0, false), 0, false, Point2D(3, 3), 0, 0, 0, 1, Cell(0, 0), 0);
                    if (cell != unknown_geometry_k) {
                        best_distance = distance;
                        best_cell = cell;
                    }
                }
            }
        }
    }

    if (best_distance != -1) {
        if (best_distance < 256) {
            Cell cell = Map.Unknown_005502E0(unknown_slot104(), 0, Map.Zone(unknown_slot104(), 0, false), 0, false, Point2D(1, 1), 0, 0, 0, 1, Cell(0, 0), 0);
            return &Map[cell];
        }
        return &Map[best_cell];
    }

    for (index = 0; index < unknown_objects_a40368.Count(); index++) {
        TechnoClass *techno = unknown_objects_a40368[index]->As_Techno();
        if (techno && !techno->unknown_76 && techno->House == House && techno != this) {
            int distance = Coord_Distance(Center_Coord(), techno->Center_Coord());
            if (best_distance == -1 || distance < best_distance) {
                Cell cell = techno->unknown_slot104();
                cell = Map.Unknown_005502E0(cell, 0, Map.Zone(cell, 0, false), 0, false, Point2D(1, 1), 0, 0, 0, 1, Cell(0, 0), 0);
                if (cell != unknown_geometry_k) {
                    best_distance = distance;
                    best_cell = cell;
                }
            }
        }
    }
    if (best_distance != -1) {
        return &Map[best_cell];
    }
    return &Map[(CoordStruct)Coord];
}
