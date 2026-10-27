// int AircraftClass::unknown_slot134() (0x00415300, slot 134)
// Without +0x494: target the cell the map finds on the house's edge (+0x128,
// 0 when out of range) unless it finds none. With +0x494: clear the target
// once slot 105 answers it. Always 3.
#include "shared/aircraft.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0049A700@DisplayClass@@QAE?AVCell@@HABV2@0HHH@Z=0049a700
// @ref _unknown_geometry_k=0083c478

int AircraftClass::unknown_slot134()
{
    if (unknown_494 == 0) {
        int edge = House->unknown_128;
        if (edge < 0 || edge > 3) {
            edge = 0;
        }
        Cell cell = Map.Unknown_0049A700(edge, unknown_geometry_k, unknown_geometry_k, 4, 1, 0);
        if (cell.X != unknown_geometry_k.X || cell.Y != unknown_geometry_k.Y) {
            unknown_slot260((AbstractClass *)&Map[cell], 1);
            return 3;
        }
    } else if (unknown_494 == unknown_slot105()) {
        unknown_slot260(0, 1);
    }
    return 3;
}
